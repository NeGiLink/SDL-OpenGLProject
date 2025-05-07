#include "Skeleton.h"


bool Skeleton::Load(const string& fileName)
{
	// �t�@�C���̊g���q���擾
	string extension = fileName.substr(fileName.find_last_of('.') + 1);

	// **FBX �̏ꍇ**
	if (extension == "fbx")
	{
		return LoadFromFBX(fileName);
	}

	// **JSON �̏ꍇ�i�]���̏����j**
	return LoadFromJSON(fileName);
}

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

	if (count > MAX_SKELETON_BONES)
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

		temp.mLocalBindPose.mRotation.x = rot[0].GetDouble();
		temp.mLocalBindPose.mRotation.y = rot[1].GetDouble();
		temp.mLocalBindPose.mRotation.z = rot[2].GetDouble();
		temp.mLocalBindPose.mRotation.w = rot[3].GetDouble();

		temp.mLocalBindPose.mPosition.x = trans[0].GetDouble();
		temp.mLocalBindPose.mPosition.y = trans[1].GetDouble();
		temp.mLocalBindPose.mPosition.z = trans[2].GetDouble();

		mBones.emplace_back(temp);
	}

	// Now that we have the bones
	ComputeGlobalInvBindPose();

	return true;
}


bool Skeleton::LoadFromFBX(const string& fileName)
{
	//�t�@�C���ǂݍ���
	Assimp::Importer importer;
	//�O�p�`�Ń|���S�����擾�A�{�[���̃E�F�C�g���ő�4�ɐ����A�X�P�[�����O��1unit��
	const aiScene* scene = importer.ReadFile(fileName,
		aiProcess_Triangulate | aiProcess_LimitBoneWeights |
		aiProcess_GlobalScale | aiProcess_MakeLeftHanded |
		aiProcess_FlipUVs |
		aiProcess_FlipWindingOrder);
	//���f�������邩�m�F
	if (!scene || !scene->HasMeshes()) {
		//�Ȃ��Ȃ�G���[���b�Z�[�W
		SDL_Log("Failed to load FBX: %s", importer.GetErrorString());
		return false;
	}
	//�{�[���̏�����
	mBones.clear();
	//���b�V���̐���for��
	for (unsigned int i = 0; i < scene->mNumMeshes; i++) 
	{
		aiMesh* mesh = scene->mMeshes[i];
		//���b�V�����̃{�[������for��
		for (unsigned int j = 0; j < mesh->mNumBones; j++) 
		{
			//�{�[�����擾
			aiBone* bone = mesh->mBones[j];
			//�{�[�������擾
			string boneName = bone->mName.C_Str();
			//�擾�����{�[��������Z�k�������O�ɕϊ��������̂��擾
			string boneShortName = ConvertSimpleBoneName(bone->mName.C_Str());
			//boneNameToIndex�ɂ��łɓ����{�[�����Ȃ����`�F�b�N
			if (boneNameToIndex.find(boneName) != boneNameToIndex.end()) continue;
			//�{�[���̍\����
			Bone boneStruct;
			//�{�[����mOffsetMatrix��vector�Ɋi�[
			mOffsetMatrix.push_back(bone->mOffsetMatrix);
			//�{�[���{���̖��O����
			boneStruct.mName = boneName;
			//�{�[���̒Z�k������
			boneStruct.mShortName = boneShortName;
			// ��� SetParentBones() �Őݒ肷��
			boneStruct.mParent = -1;

			// �o�C���h�|�[�Y�̕ϊ�
			//�{�[����mOffsetMatrix�擾
			aiMatrix4x4 bindPose = bone->mOffsetMatrix;
			aiVector3D pos;
			aiQuaternion rot;
			aiVector3D scale;
			//�{�[���̃o�C���h�|�[�Y���e�l�ɕ���
			bindPose.Decompose(scale, rot, pos);

			//rot.x = -rot.x;
			//pos.x = -pos.x;
			//���[�J���̃o�C���h�|�[�Y�ɉ�]�A���s�ړ��A�X�P�[�����O���i�[
			boneStruct.mLocalBindPose.mRotation = Quaternion(rot.x, rot.y, rot.z, rot.w);
			boneStruct.mLocalBindPose.mPosition = Vector3(pos.x, pos.y, pos.z);
			boneStruct.mLocalBindPose.mScale = Vector3(scale.x, scale.y, scale.z);
			//boneNameToIndex�Ƀ{�[�������L�[�Ƀ{�[���ԍ����i�[
			boneNameToIndex[boneName] = static_cast<int>(mBones.size());
			//������mBoneTransform�Ƀ{�[���̔ԍ����i�[
			mBoneTransform[boneStruct.mShortName] = static_cast<int>(mBones.size());
			//�{�[���x�N�^�[�Ɋi�[
			mBones.push_back(boneStruct);

			//assimp�ł̓I�t�Z�b�g�s������̂܂ܗ��p
			mGlobalInvBindPoses.push_back(boneStruct.mLocalBindPose.ToMatrix());
			//�{�[���̃I�u�W�F�N�g�𐶐�
			BoneActor* boneActor = new BoneActor();
			boneActor->SetBoneIndex(static_cast<int>(mBones.size()));
			boneActor->SetBoneName(boneShortName);
			mBoneActors.push_back(boneActor);
		}
	}

	// �e�q�֌W��ݒ�
	SetParentBones(scene->mRootNode, -1);
	return true;
}

void Skeleton::SetParentBones(aiNode* node, int parentIndex)
{
	//�s���ȃ{�[���̏ꍇ�Ɏ��ɂ��̂܂܍ċN���邽�߂̏�����ǉ�
	string nodeName = node->mName.data;
	int nextIndex = parentIndex;

	// ���̃m�[�h���{�[���Ƃ��ēo�^����Ă��邩�m�F
	if (boneNameToIndex.find(nodeName) != boneNameToIndex.end()) 
	{
		int boneIndex = boneNameToIndex[nodeName];
		mBones[boneIndex].mParent = parentIndex;
		nextIndex = boneIndex;

		//�o�C���h�|�[�Y�����[�J�����ɕϊ�
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

		mBones[boneIndex].mLocalBindPose.mRotation = Quaternion(rot.x, rot.y, rot.z, rot.w);
		mBones[boneIndex].mLocalBindPose.mPosition = Vector3(pos.x, pos.y, pos.z);
		mBones[boneIndex].mLocalBindPose.mScale = Vector3(scale.x, scale.y, scale.z);
	}

	// �q�m�[�h���ċA�I�ɏ���
	for (unsigned int i = 0; i < node->mNumChildren; i++) 
	{
		SetParentBones(node->mChildren[i], nextIndex);
	}
}

string Skeleton::ConvertSimpleBoneName(string boneName)
{
	string bone = boneName;
	// �e�{�[���̕��ʂ̖��O�̔z��
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

bool Skeleton::EndsWith(const string& str, const string& suffix)
{
	if (str.size() < suffix.size()) return false;
	return str.substr(str.size() - suffix.size()) == suffix;
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