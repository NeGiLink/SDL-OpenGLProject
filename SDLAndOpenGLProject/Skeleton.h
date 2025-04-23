#pragma once
#include "BoneTransform.h"
#include "BoneActor.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <assimp/mesh.h>

class Skeleton
{
public:
	//�X�P���g���̃^�C�v�̃^�O
	enum SkeletonType 
	{
		Humanoid,
		Generic
	};
	// ���i�̊e���̒�`
	struct Bone
	{
		BoneTransform mLocalBindPose;
		std::string mName;
		std::string mGetName;
		int mParent;
	};

	bool Load(const std::string& fileName);

	// �t�@�C������ǂݍ���
	bool LoadFromJSON(const std::string& fileName);

	bool LoadFromFBX(const std::string& fileName);

	void SetParentBones(aiNode* node, int parentIndex);

	std::string ConvertSimpleBoneName(std::string boneName);

	bool EndsWith(const std::string& str, const std::string& suffix);



	// Getter functions
	size_t GetNumBones() const { return mBones.size(); }

	const Bone& GetBone(size_t idx) const { return mBones[idx]; }
	
	const std::vector<Bone>& GetBones() const { return mBones; }

	std::vector<BoneActor*> GetBoneActor() const { return mBoneActors; }
	
	const std::vector<Matrix4>& GetGlobalInvBindPoses() const { return mGlobalInvBindPoses; }

	//�A�j���[�V�����K�p��̃{�[���̍s��ϐ���Getter
	const std::vector<Matrix4>& GetGlobalCurrentPoses() const { return mGlobalCurrentPoses; }
	//�A�j���[�V�����K�p��̊e�{�[���̍s����Z�b�g����Setter
	void SetGlobalCurrentPoses(std::vector<Matrix4>& poses) { mGlobalCurrentPoses = poses; }
	
	const std::unordered_map<std::string, int>& GetBoneNameToIndex() const { return boneNameToIndex; }

	Matrix4 GetBonePosition(std::string boneName);
	//�w�肵���{�[���ɃI�u�W�F�N�g���q�I�u�W�F�N�g�Ƃ��Đݒ�
	void AddBoneChildActor(std::string boneName,class ActorObject* actor);

	void SetParentActor(ActorObject* parent);
protected:
	// �X�P���g�������[�h�����Ǝ����I�ɌĂяo����A
	// �e�{�[���̃O���[�o���C���o�C���h�|�[�Y���v�Z�B
	void ComputeGlobalInvBindPose();
private:
	// ���i�̍�
	std::vector<Bone>						mBones;
	std::vector<BoneActor*>					mBoneActors;
	//�v�Z�p�̃I�t�Z�b�g�ϐ�
	std::vector<aiMatrix4x4>				mOffsetMatrix;
	// �eBone�ɑ΂���O���[�o���t�����|�[�Y
	std::vector<Matrix4>					mGlobalInvBindPoses;
	//�X�P���g���̃{�[���̃A�j���[�V�����K�p��̍��W�����}�g���b�N�X
	std::vector<Matrix4>					mGlobalCurrentPoses;

	std::unordered_map<std::string, int>	boneNameToIndex;

	std::unordered_map<std::string,int>		mBoneTransform;

	SkeletonType							mSkeletonType;
};