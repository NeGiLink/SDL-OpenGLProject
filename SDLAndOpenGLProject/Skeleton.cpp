#include "Skeleton.h"


bool Skeleton::Load(const string& fileName)
{
	// ファイルの拡張子を取得
	string extension = fileName.substr(fileName.find_last_of('.') + 1);

	// **FBX の場合**
	if (extension == "fbx")
	{
		return LoadFromFBX(fileName);
	}
	/*
	// **JSON の場合（従来の処理）**
	else if(extension == "gpmesh")
	{
		return LoadFromJSON(fileName);
	}
	*/

	return false;
}

bool Skeleton::LoadFromSkeletonBin(const string& fileName)
{
	string name = StringConverter::RemoveString(fileName, Model::ModelPath);
	name = StringConverter::RemoveExtension(name);
	std::ifstream in(Model::BinaryFilePath + name + Model::BinarySkelPath, std::ios::binary);
	if (!in)
	{
		SDL_Log("Failed to open Skeleton bin: %s", fileName.c_str());
		return false;
	}

	uint32_t boneCount = 0;
	in.read((char*)&boneCount, sizeof(uint32_t));

	if (boneCount > SkeletonLayout::MAX_SKELETON_BONES)
	{
		SDL_Log("Skeleton bin exceeds max bones");
		return false;
	}

	mBones.clear();
	mBones.reserve(boneCount);

	for (uint32_t i = 0; i < boneCount; ++i)
	{
		SkeletonBinBone bin{};
		in.read((char*)&bin, sizeof(SkeletonBinBone));

		Bone b;
		b.mName = bin.name;
		b.mShortName = bin.shortName;
		b.mParent = bin.parentIndex;
		b.mLocalBindPose.SetPosition(bin.position);
		b.mLocalBindPose.SetRotation(bin.rotation);
		b.mLocalBindPose.SetScale(bin.scale);

		//boneNameToIndexにボーン名をキーにボーン番号を格納
		mBoneNameToIndex[b.mName] = static_cast<int>(mBones.size());
		//同じくmBoneTransformにボーンの番号を格納
		mBoneTransform[b.mShortName] = static_cast<int>(mBones.size());

		//ボーンベクターに格納
		mBones.push_back(b);

		//assimpではオフセット行列をそのまま利用
		mGlobalInvBindPoses.push_back(b.mLocalBindPose.ToMatrix());


		//ボーンのオブジェクトを生成
		BoneActor* boneActor = new BoneActor();
		boneActor->SetBoneIndex(static_cast<int>(mBones.size()));
		boneActor->SetBoneName(b.mShortName);
		mBoneActors.push_back(boneActor);
	}

	ComputeGlobalInvBindPose();
	return true;
}
/*
bool Skeleton::LoadFromJSON(const string& fileName)
{
	std::ifstream file(fileName);
	if (!file.is_open())
	{
		SDL_Log("File not found: Skeleton %s", fileName.c_str());
		return false;
	}

	stringstream fileStream;
	fileStream << file.rdbuf();
	string contents = fileStream.str();
	rapidjson::StringStream jsonStr(contents.c_str());
	rapidjson::Document doc;
	doc.ParseStream(jsonStr);

	if (!doc.IsObject())
	{
		SDL_Log("Skeleton %s is not valid json", fileName.c_str());
		return false;
	}

	int ver = doc["version"].GetInt();

	// Check the metadata
	if (ver != 1)
	{
		SDL_Log("Skeleton %s unknown format", fileName.c_str());
		return false;
	}

	const rapidjson::Value& bonecount = doc["bonecount"];
	if (!bonecount.IsUint())
	{
		SDL_Log("Skeleton %s doesn't have a bone count.", fileName.c_str());
		return false;
	}

	size_t count = bonecount.GetUint();

	if (count > SkeletonLayout::MAX_SKELETON_BONES)
	{
		SDL_Log("Skeleton %s exceeds maximum bone count.", fileName.c_str());
		return false;
	}

	mBones.reserve(count);

	const rapidjson::Value& bones = doc["bones"];
	if (!bones.IsArray())
	{
		SDL_Log("Skeleton %s doesn't have a bone array?", fileName.c_str());
		return false;
	}

	if (bones.Size() != count)
	{
		SDL_Log("Skeleton %s has a mismatch between the bone count and number of bones", fileName.c_str());
		return false;
	}

	Bone temp;

	for (rapidjson::SizeType i = 0; i < count; i++)
	{
		if (!bones[i].IsObject())
		{
			SDL_Log("Skeleton %s: Bone %d is invalid.", fileName.c_str(), i);
			return false;
		}

		const rapidjson::Value& name = bones[i]["name"];
		temp.mName = name.GetString();

		const rapidjson::Value& parent = bones[i]["parent"];
		temp.mParent = parent.GetInt();

		const rapidjson::Value& bindpose = bones[i]["bindpose"];
		if (!bindpose.IsObject())
		{
			SDL_Log("Skeleton %s: Bone %d is invalid.", fileName.c_str(), i);
			return false;
		}

		const rapidjson::Value& rot = bindpose["rot"];
		const rapidjson::Value& trans = bindpose["trans"];

		if (!rot.IsArray() || !trans.IsArray())
		{
			SDL_Log("Skeleton %s: Bone %d is invalid.", fileName.c_str(), i);
			return false;
		}

		Quaternion rotation(rot[0].GetDouble(), rot[1].GetDouble(), rot[2].GetDouble(), rot[3].GetDouble());

		temp.mLocalBindPose.SetRotation(rotation);


		Vector3 position(trans[0].GetDouble(), trans[1].GetDouble(), trans[2].GetDouble());

		temp.mLocalBindPose.SetPosition(position);


		mBones.emplace_back(temp);
	}

	// Now that we have the bones
	ComputeGlobalInvBindPose();

	return true;
}
*/


bool Skeleton::LoadFromFBX(const string& fileName)
{
	//ファイル読み込み
	Assimp::Importer importer;
	//三角形でポリゴンを取得、ボーンのウェイトを最大4つに制限、スケーリングを1unitに
	const aiScene* scene = importer.ReadFile(fileName,
		aiProcess_Triangulate | aiProcess_LimitBoneWeights |
		aiProcess_GlobalScale | aiProcess_MakeLeftHanded |
		aiProcess_FlipUVs |
		aiProcess_FlipWindingOrder);
	//モデルがあるか確認
	if (!scene || !scene->HasMeshes()) {
		//ないならエラーメッセージ
		SDL_Log("Failed to load FBX: %s", importer.GetErrorString());
		return false;
	}
	//ボーンの初期化
	mBones.clear();
	//メッシュの数でfor文
	for (unsigned int i = 0; i < scene->mNumMeshes; i++) 
	{
		aiMesh* mesh = scene->mMeshes[i];
		//メッシュ内のボーン数でfor文
		for (unsigned int j = 0; j < mesh->mNumBones; j++) 
		{
			//ボーンを取得
			aiBone* bone = mesh->mBones[j];
			//ボーン名を取得
			string boneName = bone->mName.C_Str();
			//取得したボーン名から短縮した名前に変換したものを取得
			string boneShortName = ConvertSimpleBoneName(bone->mName.C_Str());
			//boneNameToIndexにすでに同じボーンがないかチェック
			if (mBoneNameToIndex.find(boneName) != mBoneNameToIndex.end()) continue;
			//ボーンの構造体
			Bone boneStruct;
			//ボーンのmOffsetMatrixをvectorに格納
			mOffsetMatrix.push_back(bone->mOffsetMatrix);
			//ボーン本来の名前を代入
			boneStruct.mName = boneName;
			//ボーンの短縮名を代入
			boneStruct.mShortName = boneShortName;
			// 後で SetParentBones() で設定する
			boneStruct.mParent = -1;

			// バインドポーズの変換
			//ボーンのmOffsetMatrix取得
			aiMatrix4x4 bindPose = bone->mOffsetMatrix;
			aiVector3D pos;
			aiQuaternion rot;
			aiVector3D scale;
			//ボーンのバインドポーズを各値に分解
			bindPose.Decompose(scale, rot, pos);

			//rot.x = -rot.x;
			//pos.x = -pos.x;
			//ローカルのバインドポーズに回転、平行移動、スケーリングを格納
			boneStruct.mLocalBindPose.SetRotation(Quaternion(rot.x, rot.y, rot.z, rot.w));
			boneStruct.mLocalBindPose.SetPosition(Vector3(pos.x, pos.y, pos.z));
			boneStruct.mLocalBindPose.SetScale(Vector3(scale.x, scale.y, scale.z));
			//boneNameToIndexにボーン名をキーにボーン番号を格納
			mBoneNameToIndex[boneName] = static_cast<int>(mBones.size());
			//同じくmBoneTransformにボーンの番号を格納
			mBoneTransform[boneStruct.mShortName] = static_cast<int>(mBones.size());
			//ボーンベクターに格納
			mBones.push_back(boneStruct);

			//assimpではオフセット行列をそのまま利用
			mGlobalInvBindPoses.push_back(boneStruct.mLocalBindPose.ToMatrix());
			//ボーンのオブジェクトを生成
			BoneActor* boneActor = new BoneActor();
			boneActor->SetBoneIndex(static_cast<int>(mBones.size()));
			boneActor->SetBoneName(boneShortName);
			mBoneActors.push_back(boneActor);
		}
	}

	// 親子関係を設定
	SetParentBones(scene->mRootNode, -1);

	//fileNameからPath部分だけ取り除く
	string result = StringConverter::RemoveString(fileName, Model::ModelPath);
	result = StringConverter::RemoveExtension(result);
	std::ofstream out(Model::BinaryFilePath + result + Model::BinarySkelPath, std::ios::binary);
	if (!out)
	{
		SDL_Log("Failed to open skelbin for writing.");
		return false;
	}

	uint32_t boneCount = static_cast<uint32_t>(mBones.size());
	out.write((char*)&boneCount, sizeof(uint32_t));

	for (Bone& b : mBones)
	{
		SkeletonBinBone bin{};
		strncpy_s(bin.name, b.mName.c_str(), SkeletonLayout::MAX_SKELETONBINBONE);
		strncpy_s(bin.shortName, b.mShortName.c_str(), SkeletonLayout::MAX_SKELETONBINBONE);
		bin.parentIndex = b.mParent;
		bin.position = b.mLocalBindPose.GetPosition();
		bin.rotation = b.mLocalBindPose.GetRotation();
		bin.scale = b.mLocalBindPose.GetScale();

		out.write((char*)&bin, sizeof(SkeletonBinBone));
	}

	return true;
}

void Skeleton::SetParentBones(aiNode* node, int parentIndex)
{
	//不明なボーンの場合に次にそのまま再起するための処理を追加
	string nodeName = node->mName.data;
	int nextIndex = parentIndex;

	// このノードがボーンとして登録されているか確認
	if (mBoneNameToIndex.find(nodeName) != mBoneNameToIndex.end()) 
	{
		int boneIndex = mBoneNameToIndex[nodeName];
		mBones[boneIndex].mParent = parentIndex;
		nextIndex = boneIndex;

		//バインドポーズをローカル情報に変換
		aiMatrix4x4 localMatrix = mOffsetMatrix[boneIndex];
		localMatrix = localMatrix.Inverse();

		if (parentIndex >= 0)
		{
			aiMatrix4x4 parentMatrixInv = mOffsetMatrix[parentIndex];
			localMatrix = parentMatrixInv * localMatrix;
		}

		aiVector3D pos;
		aiQuaternion rot;
		aiVector3D scale;
		localMatrix.Decompose(scale, rot, pos);

		mBones[boneIndex].mLocalBindPose.SetRotation(Quaternion(rot.x, rot.y, rot.z, rot.w));
		mBones[boneIndex].mLocalBindPose.SetPosition(Vector3(pos.x, pos.y, pos.z));
		mBones[boneIndex].mLocalBindPose.SetScale(Vector3(scale.x, scale.y, scale.z));
	}

	// 子ノードを再帰的に処理
	for (unsigned int i = 0; i < node->mNumChildren; i++) 
	{
		SetParentBones(node->mChildren[i], nextIndex);
	}
}

string Skeleton::ConvertSimpleBoneName(string boneName)
{
	string bone = boneName;
	// 各ボーンの部位の名前の配列
	vector<string> boneNames = {
		"Hips","Spine","Chest","Neck","Head",
		"LeftShoulder","LeftArm","LeftForeArm","LeftHand",
		"RightShoulder","RightArm","RightForeArm","RightHand",
		"LeftUpLeg","LeftLeg","LeftFoot",
		"RightUpLeg","RightLeg","RightFoot",
	};
	for (string bonename : boneNames) 
	{
		if (bone.find(bonename) != string::npos && EndsWith(bone, bonename)) 
		{
			bone = bonename;
		}
	}
	return bone;
}

Matrix4 Skeleton::GetBonePosition(string boneName)
{
	Matrix4 boneMatrix;
	int index = 0;
	if (mBoneTransform.find(boneName) != mBoneTransform.end())
	{
		index = mBoneTransform[boneName];
	}
	boneMatrix = mGlobalCurrentPoses[index];
	
	return boneMatrix;
}

void Skeleton::AddBoneChildActor(string boneName, class ActorObject* actor)
{
	int index = 0;
	if (mBoneTransform.find(boneName) != mBoneTransform.end())
	{
		index = mBoneTransform[boneName];
	}
	mBoneActors[index]->AddChildActor(actor);
}

void Skeleton::SetParentActor(ActorObject* parent)
{
	for (unsigned int i = 0; i < mBoneActors.size(); i++)
	{
		mBoneActors[i]->SetParentActor(parent);
	}
}

void Skeleton::ComputeGlobalInvBindPose()
{
	// Resize to number of bones, which automatically fills identity
	mGlobalInvBindPoses.resize(GetNumBones());

	// Step 1: Compute global bind pose for each bone

	// The global bind pose for root is just the local bind pose
	mGlobalInvBindPoses[0] = mBones[0].mLocalBindPose.ToMatrix();

	// Each remaining bone's global bind pose is its local pose
	// multiplied by the parent's global bind pose
	for (size_t i = 1; i < mGlobalInvBindPoses.size(); i++)
	{
		Matrix4 localMat = mBones[i].mLocalBindPose.ToMatrix();
		mGlobalInvBindPoses[i] = localMat * mGlobalInvBindPoses[mBones[i].mParent];
	}

	// Step 2: Invert
	for (size_t i = 0; i < mGlobalInvBindPoses.size(); i++)
	{
		mGlobalInvBindPoses[i].Invert();
	}
}