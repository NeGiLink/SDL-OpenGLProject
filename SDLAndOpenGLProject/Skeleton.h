#pragma once
#include "BoneTransform.h"
#include "BoneActor.h"
#include "Assimp.h"
#include "MatrixPalette.h"
#include <GL/glew.h>
#include "Actor.h"

//���Ќ������������t�@�C��

//�X�P���g���̃o�C�i���f�[�^�\����
struct SkeletonBinBone
{
	// �{�[�����i�Œ蒷�j
	char		name[64];       
	// �Z�k�Ń{�[����
	char		shortName[64];
	// �e�{�[���C���f�b�N�X�i-1 �Ȃ� root�j
	int32_t		parentIndex;      
	// �o�C���h�|�[�Y�̈ʒu
	Vector3		position;         
	// �o�C���h�|�[�Y�̉�]
	Quaternion	rotation;      
	// �o�C���h�|�[�Y�̃X�P�[���i�I�v�V�����j
	Vector3		scale;            
};

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
		BoneTransform	mLocalBindPose;
		string			mName;
		string			mShortName;
		int				mParent;
	};
protected:
	// �X�P���g�������[�h�����Ǝ����I�ɌĂяo����A
	// �e�{�[���̃O���[�o���C���o�C���h�|�[�Y���v�Z�B
	void									ComputeGlobalInvBindPose();
private:
	// ���i�̍�
	vector<Bone>							mBones;
	vector<BoneActor*>						mBoneActors;
	//�v�Z�p�̃I�t�Z�b�g�ϐ�
	vector<aiMatrix4x4>						mOffsetMatrix;
	// �eBone�ɑ΂���O���[�o���t�����|�[�Y
	vector<Matrix4>							mGlobalInvBindPoses;
	//�X�P���g���̃{�[���̃A�j���[�V�����K�p��̍��W�����}�g���b�N�X
	vector<Matrix4>							mGlobalCurrentPoses;
	//�������int�^�̘A�z�z��
	std::unordered_map<string, int>			mBoneNameToIndex;
	//�������int�^�̘A�z�z��
	std::unordered_map<string, int>			mBoneTransform;
	// �X�P���g���̃^�C�v
	// ���݂͖��g�p
	//SkeletonType							mSkeletonType;
public:
	//���ׂẴt�@�C���`������ǂݍ���
	bool									Load(const string& fileName);
	//�o�C�i���f�[�^����ǂݍ���
	bool									LoadFromSkeletonBin(const string& fileName);

	// JSON�t�@�C������ǂݍ���
	bool									LoadFromJSON(const string& fileName);
	//FBX�t�@�C������ǂݍ���
	bool									LoadFromFBX(const string& fileName);
	//�{�[���̐e��ݒ�
	void									SetParentBones(aiNode* node, int parentIndex);
	//�{�[���̖��O��Z�k���ďo��
	string									ConvertSimpleBoneName(string boneName);

	bool EndsWith(const std::string& str, const std::string& suffix)
	{
		if (str.size() < suffix.size())
		{
			return false;
		}
		return str.substr(str.size() - suffix.size()) == suffix;
	}

	// �{�[������Getter
	size_t									GetNumBones() const { return mBones.size(); }
	//�{�[����Getter Ver.1
	const Bone&								GetBone(size_t idx) const { return mBones[idx]; }
	//�{�[��Getter Ver.2
	const vector<Bone>&						GetBones() const { return mBones; }
	//�{�[���I�u�W�F�N�g��Getter
	vector<BoneActor*>						GetBoneActor() const { return mBoneActors; }
	//�{�[���̃O���[�o���o�C���h�|�[�Y��Getter
	const vector<Matrix4>&					GetGlobalInvBindPoses() const { return mGlobalInvBindPoses; }
	//�A�j���[�V�����K�p��̃{�[���̍s��ϐ���Getter
	const vector<Matrix4>&					GetGlobalCurrentPoses() const { return mGlobalCurrentPoses; }
	//�A�j���[�V�����K�p��̊e�{�[���̍s����Z�b�g����Setter
	void									SetGlobalCurrentPoses(vector<Matrix4>& poses) { mGlobalCurrentPoses = poses; }
	//�{�[���̘A�z�z���Getter
	const std::unordered_map<string, int>&	GetBoneNameToIndex() const { return mBoneNameToIndex; }
	//�{�[�������炻�̃{�[���̃}�g���b�N�X�̎擾
	Matrix4									GetBonePosition(string boneName);
	//�w�肵���{�[���ɃI�u�W�F�N�g���q�I�u�W�F�N�g�Ƃ��Đݒ�
	void									AddBoneChildActor(string boneName,class ActorObject* actor);
	//ActorObject�̐e��ݒ�
	void									SetParentActor(ActorObject* parent);
};