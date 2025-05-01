#pragma once
#include "BoneTransform.h"
#include "BoneActor.h"
#include "Assimp.h"
#include "MatrixPalette.h"
#include <GL/glew.h>
#include "Actor.h"


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
		string mName;
		string mShortName;
		int mParent;
	};

	bool Load(const string& fileName);

	// �t�@�C������ǂݍ���
	bool LoadFromJSON(const string& fileName);

	bool LoadFromFBX(const string& fileName);

	void SetParentBones(aiNode* node, int parentIndex);

	string ConvertSimpleBoneName(string boneName);

	bool EndsWith(const string& str, const string& suffix);

	aiVector3D GetTranslation(const aiMatrix4x4& matrix) {
		return aiVector3D(matrix.a4, matrix.b4, matrix.c4);
	}

	// Getter functions
	size_t GetNumBones() const { return mBones.size(); }

	const Bone& GetBone(size_t idx) const { return mBones[idx]; }
	
	const vector<Bone>& GetBones() const { return mBones; }

	vector<BoneActor*> GetBoneActor() const { return mBoneActors; }
	
	const vector<Matrix4>& GetGlobalInvBindPoses() const { return mGlobalInvBindPoses; }

	//�A�j���[�V�����K�p��̃{�[���̍s��ϐ���Getter
	const vector<Matrix4>& GetGlobalCurrentPoses() const { return mGlobalCurrentPoses; }
	//�A�j���[�V�����K�p��̊e�{�[���̍s����Z�b�g����Setter
	void SetGlobalCurrentPoses(vector<Matrix4>& poses) { mGlobalCurrentPoses = poses; }
	
	const std::unordered_map<string, int>& GetBoneNameToIndex() const { return boneNameToIndex; }

	Matrix4 GetBonePosition(string boneName);
	//�w�肵���{�[���ɃI�u�W�F�N�g���q�I�u�W�F�N�g�Ƃ��Đݒ�
	void AddBoneChildActor(string boneName,class ActorObject* actor);

	void SetParentActor(ActorObject* parent);
protected:
	// �X�P���g�������[�h�����Ǝ����I�ɌĂяo����A
	// �e�{�[���̃O���[�o���C���o�C���h�|�[�Y���v�Z�B
	void ComputeGlobalInvBindPose();
private:
	// ���i�̍�
	vector<Bone>						mBones;
	vector<BoneActor*>					mBoneActors;
	//�v�Z�p�̃I�t�Z�b�g�ϐ�
	vector<aiMatrix4x4>				mOffsetMatrix;
	// �eBone�ɑ΂���O���[�o���t�����|�[�Y
	vector<Matrix4>					mGlobalInvBindPoses;
	//�X�P���g���̃{�[���̃A�j���[�V�����K�p��̍��W�����}�g���b�N�X
	vector<Matrix4>					mGlobalCurrentPoses;

	std::unordered_map<string, int>	boneNameToIndex;

	std::unordered_map<string,int>		mBoneTransform;

	SkeletonType							mSkeletonType;
};