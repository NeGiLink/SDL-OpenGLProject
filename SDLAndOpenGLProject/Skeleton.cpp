#include "Skeleton.h"
#include <fstream>
#include <sstream>
#include <rapidjson/document.h>
#include <SDL3/SDL_log.h>
#include "MatrixPalette.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <GL/glew.h>
#include <vector>
#include <iostream>

#include <assimp/matrix4x4.h>


bool Skeleton::Load(const std::string& fileName)
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

bool Skeleton::LoadFromJSON(const std::string& fileName)
{
	std::ifstream file(fileName);
	if (!file.is_open())
	{
		SDL_Log("File not found: Skeleton %s", fileName.c_str());
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


bool Skeleton::LoadFromFBX(const std::string& fileName)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(fileName,
		aiProcess_Triangulate | aiProcess_LimitBoneWeights);

	if (!scene || !scene->HasMeshes()) {
		SDL_Log("Failed to load FBX: %s", importer.GetErrorString());
		return false;
	}

	mBones.clear();

	for (unsigned int i = 0; i < scene->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[i];

		for (unsigned int j = 0; j < mesh->mNumBones; j++) {
			aiBone* bone = mesh->mBones[j];
			std::string boneName = bone->mName.C_Str();
			std::string boneGetName = ConvertSimpleBoneName(bone->mName.C_Str());

			if (boneNameToIndex.find(boneName) != boneNameToIndex.end()) continue;

			Bone newBone;
			//TODO�F��̌v�Z�p�ɃI�t�Z�b�g��ۑ����Ă���
			//		�����̂܂܂��ƃQ�[����Bone����assimp�̏����܂߂Ă��܂����ߕύX����ׂ�
			newBone.mOffsetMatrix = bone->mOffsetMatrix;
			newBone.mName = boneName;
			newBone.mGetName = boneGetName;
			newBone.mParent = -1;  // ��� SetParentBones() �Őݒ肷��

			// �o�C���h�|�[�Y�̕ϊ�
			aiMatrix4x4 bindPose = bone->mOffsetMatrix;
			aiVector3D pos;
			aiQuaternion rot;
			aiVector3D scale;
			bindPose.Decompose(scale, rot, pos);

			newBone.mLocalBindPose.mRotation = Quaternion(rot.x, rot.y, rot.z, rot.w);
			newBone.mLocalBindPose.mPosition = Vector3(pos.x, pos.y, pos.z);
			newBone.mLocalBindPose.mScale = Vector3(scale.x, scale.y, scale.z);

			boneNameToIndex[boneName] = static_cast<int>(mBones.size());
			mBoneTransform[newBone.mGetName] = static_cast<int>(mBones.size());
			mBones.push_back(newBone);

			//TODO : assimp�ł̓I�t�Z�b�g�s������̂܂ܗ��p
			mGlobalInvBindPoses.push_back(newBone.mLocalBindPose.ToMatrix());
		}
	}

	// �e�q�֌W��ݒ�
	SetParentBones(scene->mRootNode, -1);

	//TODO : assimp�ł̓I�t�Z�b�g�s������̂܂ܗ��p���邽�ߕs�v
	// �O���[�o���t�o�C���h�|�[�Y���v�Z
	//ComputeGlobalInvBindPose();
	return true;
}

void Skeleton::SetParentBones(aiNode* node, int parentIndex)
{
	//�s���ȃ{�[���̏ꍇ�Ɏ��ɂ��̂܂܍ċN���邽�߂̏�����ǉ�
	std::string nodeName = node->mName.data;
	int nextIndex = parentIndex;

	// ���̃m�[�h���{�[���Ƃ��ēo�^����Ă��邩�m�F
	if (boneNameToIndex.find(nodeName) != boneNameToIndex.end()) {
		int boneIndex = boneNameToIndex[nodeName];
		mBones[boneIndex].mParent = parentIndex;
		nextIndex = boneIndex;

		//TODO�F�o�C���h�|�[�Y�����[�J�����ɕϊ�
		auto localMatrix = mBones[boneIndex].mOffsetMatrix;
		localMatrix = localMatrix.Inverse();

		if (parentIndex >= 0)
		{
			auto parentMatrixInv = mBones[parentIndex].mOffsetMatrix;
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
	for (unsigned int i = 0; i < node->mNumChildren; i++) {
		SetParentBones(node->mChildren[i], nextIndex);
	}
}

std::string Skeleton::ConvertSimpleBoneName(std::string boneName)
{
	std::string bone = boneName;
	// We support these font sizes
	std::vector<std::string> bns = {
		"Hips","Spine","Chest","Neck","Head",
		"LeftShoulder","LeftArm","LeftForeArm","LeftHand",
		"RightShoulder","RightArm","RightForeArm","RightHand",
		"LeftUpLeg","LeftLeg","LeftFoot",
		"RightUpLeg","RightLeg","RightFoot",
	};
	for (std::string bn : bns) 
	{
		if (bone.find(bn) != std::string::npos && EndsWith(bone, bn)) 
		{
			bone = bn;
		}
	}
	return bone;
}

bool Skeleton::EndsWith(const std::string& str, const std::string& suffix)
{
	if (str.size() < suffix.size()) return false;
	return str.substr(str.size() - suffix.size()) == suffix;
}

Matrix4 Skeleton::GetBonePosition(std::string boneName)
{
	Matrix4 bonePos;
	int index = 0;
	if (mBoneTransform.find(boneName) != mBoneTransform.end())
	{
		index = mBoneTransform[boneName];
	}
	bonePos = mGlobalCurrentPoses[index];
	
	return bonePos;
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