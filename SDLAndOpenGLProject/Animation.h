#pragma once
#include "BoneTransform.h"
#include "Assimp.h"
#include "SDL3.h"

class Animation
{
public:
	Animation(class Skeleton* skeleton);

	bool Load(const std::string& fileName);

	size_t GetNumBones() const { return mNumBones; }
	size_t GetNumFrames() const { return mNumFrames; }
	float GetDuration() const { return mDuration; }
	float GetFrameDuration() const { return mFrameDuration; }

	// �w�肳�ꂽ�A�j���[�V�����̎��Ԃɂ�����e�{�[���̃O���[�o���i���݂́j�|�[�Y�s���񋟂��ꂽ�x�N�^�[�ɏ[�U�B
	// ���Ԃ�0.0f�ȏ��mDuration�ȉ��ł��邱�ƁB
	void GetGlobalPoseAtTime(std::vector<Matrix4>& outPoses, const class Skeleton* inSkeleton, float inTime) const;

	void SetSkeleton(class Skeleton* skeleton) { mSkeleton = skeleton; }
private:
	bool LoadFromJSON(const std::string& fileName);
	bool LoadFromFBX(const std::string& fileName);

	size_t FindTranslation(float AnimationTime, const aiNodeAnim* pNodeAnim);

	void CalcInterpolatedTranslation(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim);

	size_t FindRotation(float AnimationTime, const aiNodeAnim* pNodeAnim);

	void CalcInterpolatedRotation(aiQuaternion& Out, float AnimationTime, const aiNodeAnim* pNodeAnim);

	size_t FindScaling(float AnimationTime, const aiNodeAnim* pNodeAnim);

	void CalcInterpolatedScaling(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim);
	// �A�j���[�V�����̂��߂̍��̐�
	size_t mNumBones;
	// �A�j���[�V�����̃t���[����
	size_t mNumFrames;
	// �A�j���[�V�����̎������ԁi�b�j
	float mDuration;
	// �A�j���[�V�����ɂ�����e�t���[���̎�������
	float mFrameDuration;
	// �g���b�N��̊e�t���[���ɑ΂������ϊ��B
	// �O���̃x�N�g���̊e�C���f�b�N�X�͍��ł���A
	// �����̃x�N�g���̓t���[���ł��B
	std::vector<std::vector<BoneTransform>> mTracks;

	class Skeleton* mSkeleton;
};