#include "Animation.h"
#include "Skeleton.h"
#include <rapidjson/document.h>

Animation::Animation(Skeleton* skeleton)
	:mSkeleton(skeleton)
{
}

bool Animation::Load(const std::string& fileName)
{
	// �t�@�C���̊g���q���擾
	std::string extension = fileName.substr(fileName.find_last_of('.') + 1);

	// **FBX �̏ꍇ**
	if (extension == "fbx")
	{
		return LoadFromFBX(fileName);
	}

	// **JSON �̏ꍇ�i�]���̏����j**
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
		aiProcess_Triangulate | aiProcess_LimitBoneWeights| aiProcess_GlobalScale);

	if (!scene || !scene->HasAnimations()) {
		SDL_Log("No animations found in FBX: %s", fileName.c_str());
		return false;
	}

	aiAnimation* anim = scene->mAnimations[0];

	float ticksPerSecond = (anim->mTicksPerSecond != 0) ? anim->mTicksPerSecond : 25.0f;
	mDuration = static_cast<float>(anim->mDuration / ticksPerSecond);

	//mNumFrames ���L�[�̍ő�l�ɍ��킹��
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

	//�A�j���[�V�����Ɋ܂܂�Ă��Ȃ��{�[���̂��߂Ƀo�C���h�|�[�Y�����̂܂ܗ��p
	for (unsigned int i = 0; i < mNumBones; i++) {
		mTracks[i].resize(mNumFrames);
		auto& localBindPose = mSkeleton->GetBone(i).mLocalBindPose;
		for (size_t j = 0; j < mNumFrames; j++) {
			mTracks[i][j] = localBindPose;
		}
	}

	// �e�{�[���̃A�j���[�V�������擾
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

		//�v�Z��S�ĕ�Ԃ𗘗p
		// �t���[�����Ƃ� `BoneTransform` ���쐬
		for (size_t j = 0; j < mNumFrames; j++) {
			BoneTransform temp = mSkeleton->GetBone(boneIndex).mLocalBindPose;

			// �ʒu�L�[�̓K�p
			aiVector3D pos;
			CalcInterpolatedTranslation(pos, j, channel);
			//�ʒu�̈Ⴄ���f���̂��߂ɕω��ʂ��v�Z���ė��p
			//���̂܂܂��Ə�����Ԃňړ����Ă���ꍇ�͓K�p����Ȃ��I
			//�{���̓{�[���̌��̏�Ԃ���ω����v�Z����
			//������͂܂����C��
			aiVector3D basePos = channel->mPositionKeys[0].mValue;
			//aiVector3D basePos = aiVector3D(temp.mPosition.x, temp.mPosition.y, temp.mPosition.z);
			temp.mPosition += Vector3(pos.x - basePos.x, pos.y - basePos.y, pos.z - basePos.z);

			// ��]�L�[�̓K�p
			aiQuaternion rot;
			CalcInterpolatedRotation(rot, j, channel);
			temp.mRotation = Quaternion(rot.x, rot.y, rot.z, rot.w);

			// �X�P�[���L�[�̓K�p
			aiVector3D scale;
			CalcInterpolatedScaling(scale, j, channel);
			temp.mScale = Vector3(scale.x, scale.y, scale.z);

			// `emplace_back()` �ł͂Ȃ��A�C���f�b�N�X���
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
	// ���݂̃t���[���C���f�b�N�X�Ǝ��̃t���[������肵�܂�
	//�i����́AinTime��[0, AnimDuration]�ɐ��񂳂�Ă���Ɖ��肵�Ă��܂��j
	size_t frame = static_cast<size_t>(inTime / mFrameDuration);
	size_t nextFrame = frame + 1;
	// �t���[���Ǝ��̃t���[���̊Ԃ̕����l���v�Z����
	float pct = inTime / mFrameDuration - frame;

	// ���[�g�̃|�[�Y��ݒ肷��
	if (mTracks[0].size() > 0)
	{
		//nextFrame���ő吔�𒴂��Ă��邱�Ƃ����邽�ߑ΍�B
		if (frame >= mTracks[0].size() || nextFrame >= mTracks[0].size())
		{
			outPoses[0] = mTracks[0][mTracks[0].size() - 1].ToMatrix();
		}
		else
		{
			// ���݂̃t���[���̃|�[�Y�Ǝ��̃t���[���̊Ԃ��Ԃ���B
			BoneTransform interp = BoneTransform::Interpolate(mTracks[0][frame],
				mTracks[0][nextFrame], pct);
			outPoses[0] = interp.ToMatrix();
		}
	}
	else
	{
		outPoses[0] = Matrix4::Identity;
	}

	const std::vector<Skeleton::Bone>& bones = inSkeleton->GetBones();
	// �c��̃|�[�Y��ݒ肵�Ă��������B
	for (size_t bone = 1; bone < mNumBones; bone++)
	{
		Matrix4 localMat; // (Defaults to identity)
		if (mTracks[bone].size() > 0)
		{
			//nextFrame���ő吔�𒴂��Ă��邱�Ƃ����邽�ߑ΍�
			if (frame >= mTracks[bone].size() || nextFrame >= mTracks[bone].size())
			{
				localMat = mTracks[bone][mTracks[bone].size() - 1].ToMatrix();
			}
			else
			{
				BoneTransform interp = BoneTransform::Interpolate(mTracks[bone][frame],
					mTracks[bone][nextFrame], pct);
				localMat = interp.ToMatrix();
			}
		}
		//�e�����Ȃ��ꍇ�̑Ώ�
		if (bones[bone].mParent < 0)
		{
			outPoses[bone] = localMat;
			continue;
		}

		outPoses[bone] = localMat * outPoses[bones[bone].mParent];
	}
}

//��ԏ��̌v�Z�A�`���[�g���A��������p
// https://ogldev.org/www/tutorial38/tutorial38.html
size_t Animation::FindTranslation(float AnimationTime, const aiNodeAnim* pNodeAnim)
{
	assert(pNodeAnim->mNumScalingKeys > 0);

	for (size_t i = 0; i < pNodeAnim->mNumPositionKeys - 1; i++) {
		if (AnimationTime < (float)pNodeAnim->mPositionKeys[i + 1].mTime) {
			return i;
		}
	}

	assert(0);
}
void Animation::CalcInterpolatedTranslation(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim)
{
	if (pNodeAnim->mNumPositionKeys == 1) {
		Out = pNodeAnim->mPositionKeys[0].mValue;
		return;
	}
	if (AnimationTime >= pNodeAnim->mPositionKeys[pNodeAnim->mNumPositionKeys - 1].mTime)
	{
		Out = pNodeAnim->mPositionKeys[pNodeAnim->mNumPositionKeys - 1].mValue;
		return;
	}

	size_t TranslationIndex = FindTranslation(AnimationTime, pNodeAnim);
	size_t NextTranslationIndex = (TranslationIndex + 1);
	assert(NextTranslationIndex < pNodeAnim->mNumPositionKeys);
	float DeltaTime = pNodeAnim->mPositionKeys[NextTranslationIndex].mTime - pNodeAnim->mPositionKeys[TranslationIndex].mTime;
	float Factor = (AnimationTime - (float)pNodeAnim->mPositionKeys[TranslationIndex].mTime) / DeltaTime;
	assert(Factor >= 0.0f && Factor <= 1.0f);
	const aiVector3D& StartTranslation = pNodeAnim->mPositionKeys[TranslationIndex].mValue;
	const aiVector3D& EndTranslation = pNodeAnim->mPositionKeys[NextTranslationIndex].mValue;
	Out = StartTranslation + (EndTranslation - StartTranslation) * Factor;
}

size_t Animation::FindRotation(float AnimationTime, const aiNodeAnim* pNodeAnim)
{
	assert(pNodeAnim->mNumRotationKeys > 0);

	for (size_t i = 0; i < pNodeAnim->mNumRotationKeys - 1; i++) {
		if (AnimationTime < (float)pNodeAnim->mRotationKeys[i + 1].mTime) {
			return i;
		}
	}

	assert(0);
}
void Animation::CalcInterpolatedRotation(aiQuaternion& Out, float AnimationTime, const aiNodeAnim* pNodeAnim)
{
	if (pNodeAnim->mNumRotationKeys == 1) {
		Out = pNodeAnim->mRotationKeys[0].mValue;
		return;
	}
	if (AnimationTime >= pNodeAnim->mRotationKeys[pNodeAnim->mNumRotationKeys - 1].mTime)
	{
		Out = pNodeAnim->mRotationKeys[pNodeAnim->mNumRotationKeys - 1].mValue;
		return;
	}

	size_t RotationIndex = FindRotation(AnimationTime, pNodeAnim);
	size_t NextRotationIndex = (RotationIndex + 1);
	assert(NextRotationIndex < pNodeAnim->mNumRotationKeys);
	float DeltaTime = pNodeAnim->mRotationKeys[NextRotationIndex].mTime - pNodeAnim->mRotationKeys[RotationIndex].mTime;
	float Factor = (AnimationTime - (float)pNodeAnim->mRotationKeys[RotationIndex].mTime) / DeltaTime;
	assert(Factor >= 0.0f && Factor <= 1.0f);
	const aiQuaternion& StartRotationQ = pNodeAnim->mRotationKeys[RotationIndex].mValue;
	const aiQuaternion& EndRotationQ = pNodeAnim->mRotationKeys[NextRotationIndex].mValue;
	aiQuaternion::Interpolate(Out, StartRotationQ, EndRotationQ, Factor);
	Out = Out.Normalize();
}

size_t Animation::FindScaling(float AnimationTime, const aiNodeAnim* pNodeAnim)
{
	assert(pNodeAnim->mNumPositionKeys > 0);

	for (size_t i = 0; i < pNodeAnim->mNumScalingKeys - 1; i++) {
		if (AnimationTime < (float)pNodeAnim->mScalingKeys[i + 1].mTime) {
			return i;
		}
	}

	assert(0);
}
void Animation::CalcInterpolatedScaling(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim)
{
	if (pNodeAnim->mNumScalingKeys == 1) {
		Out = pNodeAnim->mScalingKeys[0].mValue;
		return;
	}
	if (AnimationTime >= pNodeAnim->mScalingKeys[pNodeAnim->mNumScalingKeys - 1].mTime)
	{
		Out = pNodeAnim->mScalingKeys[pNodeAnim->mNumScalingKeys - 1].mValue;
		return;
	}

	size_t ScalingIndex = FindScaling(AnimationTime, pNodeAnim);
	size_t NextScalingIndex = (ScalingIndex + 1);
	assert(NextScalingIndex < pNodeAnim->mNumScalingKeys);
	float DeltaTime = pNodeAnim->mScalingKeys[NextScalingIndex].mTime - pNodeAnim->mScalingKeys[ScalingIndex].mTime;
	float Factor = (AnimationTime - (float)pNodeAnim->mScalingKeys[ScalingIndex].mTime) / DeltaTime;
	assert(Factor >= 0.0f && Factor <= 1.0f);
	const aiVector3D& StartScaling = pNodeAnim->mScalingKeys[ScalingIndex].mValue;
	const aiVector3D& EndScaling = pNodeAnim->mScalingKeys[NextScalingIndex].mValue;
	Out = StartScaling + (EndScaling - StartScaling) * Factor;
}