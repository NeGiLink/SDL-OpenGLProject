#include "Animation.h"
#include "Skeleton.h"
#include <rapidjson/document.h>


Animation::Animation(Skeleton* skeleton)
	:mSkeleton(skeleton)
{
}

bool Animation::Load(const std::string& fileName)
{
	// ファイルの拡張子を取得
	std::string extension = fileName.substr(fileName.find_last_of('.') + 1);

	// **FBX の場合**
	if (extension == "fbx")
	{
		return LoadFromFBX(fileName);
	}

	// **JSON の場合（従来の処理）**
	return LoadFromJSON(fileName);
}

bool Animation::LoadFromJSON(const std::string& fileName)
{
	std::ifstream file(fileName);
	if (!file.is_open())
	{
		SDL_Log("File not found: Animation %s", fileName.c_str());
		return false;
	}

	std::stringstream fileStream;
	fileStream << file.rdbuf();
	std::string contents = fileStream.str();
	rapidjson::StringStream jsonStr(contents.c_str());
	rapidjson::Document doc;
	doc.ParseStream(jsonStr);

	if (!doc.IsObject())
	{
		SDL_Log("Animation %s is not valid json", fileName.c_str());
		return false;
	}

	int ver = doc["version"].GetInt();

	// Check the metadata
	if (ver != 1)
	{
		SDL_Log("Animation %s unknown format", fileName.c_str());
		return false;
	}

	const rapidjson::Value& sequence = doc["sequence"];
	if (!sequence.IsObject())
	{
		SDL_Log("Animation %s doesn't have a sequence.", fileName.c_str());
		return false;
	}

	const rapidjson::Value& frames = sequence["frames"];
	const rapidjson::Value& length = sequence["length"];
	const rapidjson::Value& bonecount = sequence["bonecount"];

	if (!frames.IsUint() || !length.IsDouble() || !bonecount.IsUint())
	{
		SDL_Log("Sequence %s has invalid frames, length, or bone count.", fileName.c_str());
		return false;
	}

	mNumFrames = frames.GetUint();
	mDuration = length.GetDouble();
	mNumBones = bonecount.GetUint();
	mFrameDuration = mDuration / (mNumFrames - 1);

	mTracks.resize(mNumBones);

	const rapidjson::Value& tracks = sequence["tracks"];

	if (!tracks.IsArray())
	{
		SDL_Log("Sequence %s missing a tracks array.", fileName.c_str());
		return false;
	}

	for (rapidjson::SizeType i = 0; i < tracks.Size(); i++)
	{
		if (!tracks[i].IsObject())
		{
			SDL_Log("Animation %s: Track element %d is invalid.", fileName.c_str(), i);
			return false;
		}

		size_t boneIndex = tracks[i]["bone"].GetUint();

		const rapidjson::Value& transforms = tracks[i]["transforms"];
		if (!transforms.IsArray())
		{
			SDL_Log("Animation %s: Track element %d is missing transforms.", fileName.c_str(), i);
			return false;
		}

		BoneTransform temp;

		if (transforms.Size() < mNumFrames)
		{
			SDL_Log("Animation %s: Track element %d has fewer frames than expected.", fileName.c_str(), i);
			return false;
		}

		for (rapidjson::SizeType j = 0; j < transforms.Size(); j++)
		{
			const rapidjson::Value& rot = transforms[j]["rot"];
			const rapidjson::Value& trans = transforms[j]["trans"];

			if (!rot.IsArray() || !trans.IsArray())
			{
				SDL_Log("Skeleton %s: Bone %d is invalid.", fileName.c_str(), i);
				return false;
			}

			temp.mRotation.x = rot[0].GetDouble();
			temp.mRotation.y = rot[1].GetDouble();
			temp.mRotation.z = rot[2].GetDouble();
			temp.mRotation.w = rot[3].GetDouble();

			temp.mPosition.x = trans[0].GetDouble();
			temp.mPosition.y = trans[1].GetDouble();
			temp.mPosition.z = trans[2].GetDouble();

			mTracks[boneIndex].emplace_back(temp);
		}
	}

	return true;
}

bool Animation::LoadFromFBX(const std::string& fileName)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(fileName,
		aiProcess_Triangulate | aiProcess_LimitBoneWeights);

	if (!scene || !scene->HasAnimations()) {
		SDL_Log("No animations found in FBX: %s", fileName.c_str());
		return false;
	}

	aiAnimation* anim = scene->mAnimations[0];

	float ticksPerSecond = (anim->mTicksPerSecond != 0) ? anim->mTicksPerSecond : 25.0f;
	mDuration = static_cast<float>(anim->mDuration / ticksPerSecond);

	// mNumFrames をキーの最大値に合わせる
	mNumFrames = 0;
	for (unsigned int i = 0; i < anim->mNumChannels; i++) {
		aiNodeAnim* channel = anim->mChannels[i];
		mNumFrames = std::max((unsigned int)mNumFrames, channel->mNumPositionKeys);
		mNumFrames = std::max((unsigned int)mNumFrames, channel->mNumRotationKeys);
		mNumFrames = std::max((unsigned int)mNumFrames, channel->mNumScalingKeys);
	}

	mFrameDuration = mDuration / (mNumFrames - 1);
	mNumBones = mSkeleton->GetBones().size();
	mTracks.resize(mNumBones);

	// 各ボーンのアニメーションを取得
	for (unsigned int i = 0; i < anim->mNumChannels; i++) {
		aiNodeAnim* channel = anim->mChannels[i];
		std::string boneName = channel->mNodeName.C_Str();

		auto it = mSkeleton->GetBoneNameToIndex().find(boneName);
		if (it == mSkeleton->GetBoneNameToIndex().end()) {
			SDL_Log("Bone %s not found in skeleton.", boneName.c_str());
			continue;
		}
		int boneIndex = it->second;

		mTracks[boneIndex].resize(mNumFrames);

		// フレームごとに `BoneTransform` を作成
		for (size_t j = 0; j < mNumFrames; j++) {
			BoneTransform temp;

			// 位置キーの適用
			if (j < channel->mNumPositionKeys) {
				aiVector3D pos = channel->mPositionKeys[j].mValue;
				temp.mPosition = Vector3(pos.x, pos.y, pos.z);
			}

			// 回転キーの適用
			if (j < channel->mNumRotationKeys) {
				aiQuaternion rot = channel->mRotationKeys[j].mValue;
				temp.mRotation = Quaternion(rot.x, rot.y, rot.z, rot.w);
			}

			// スケールキーの適用
			if (j < channel->mNumScalingKeys) {
				aiVector3D scale = channel->mScalingKeys[j].mValue;
				temp.mScale = Vector3(scale.x, scale.y, scale.z);
			}
			else {
				// デフォルトスケール
				temp.mScale = Vector3(1.0f, 1.0f, 1.0f); 
			}

			// `emplace_back()` ではなく、インデックス代入
			mTracks[boneIndex][j] = temp;
		}
	}

	return true;
}

void Animation::GetGlobalPoseAtTime(std::vector<Matrix4>& outPoses, const Skeleton* inSkeleton, float inTime) const
{
	if (outPoses.size() != mNumBones)
	{
		outPoses.resize(mNumBones);
	}

	// Figure out the current frame index and next frame
	// (This assumes inTime is bounded by [0, AnimDuration]
	size_t frame = static_cast<size_t>(inTime / mFrameDuration);
	size_t nextFrame = frame + 1;
	// Calculate fractional value between frame and next frame
	float pct = inTime / mFrameDuration - frame;

	// Setup the pose for the root
	if (mTracks[0].size() > 0)
	{
		// Interpolate between the current frame's pose and the next frame
		BoneTransform interp = BoneTransform::Interpolate(mTracks[0][frame],
			mTracks[0][nextFrame], pct);
		outPoses[0] = interp.ToMatrix();
	}
	else
	{
		outPoses[0] = Matrix4::Identity;
	}

	const std::vector<Skeleton::Bone>& bones = inSkeleton->GetBones();
	// Now setup the poses for the rest
	for (size_t bone = 1; bone < mNumBones; bone++)
	{
		Matrix4 localMat; // (Defaults to identity)
		if (mTracks[bone].size() > 0)
		{
			BoneTransform interp = BoneTransform::Interpolate(mTracks[bone][frame],
				mTracks[bone][nextFrame], pct);
			localMat = interp.ToMatrix();
		}
		//TODO : 親がいない場合の対処
		if (bones[bone].mParent < 0)
		{
			outPoses[bone] = localMat;
			continue;
		}

		outPoses[bone] = localMat * outPoses[bones[bone].mParent];
	}
}
