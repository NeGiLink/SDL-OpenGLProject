#pragma once
#include "BoneTransform.h"
#include "Assimp.h"
#include "SDL3.h"

//�A�j���[�V����1�̏������N���X
class Animation
{
public:
	Animation(class Skeleton* skeleton);

	bool Load(const std::string& fileName);

	size_t	GetNumBones() const { return mNumBones; }
	
	size_t	GetNumFrames() const { return mNumFrames; }
	
	float	GetDuration() const { return mDuration; }
	
	float	GetFrameDuration() const { return mFrameDuration; }

	void	SetSkeleton(class Skeleton* skeleton) { mSkeleton = skeleton; }

	bool	IsLoop() const { return isLoop; }

	void	SetLoop(bool loop) { isLoop = loop; }

	bool	IsAnimationEnd() const { return isAnimationEnd; }

	void	SetIsAnimationEnd(bool animationEnd) { isAnimationEnd = animationEnd; }

	// �w�肳�ꂽ�A�j���[�V�����̎��Ԃɂ�����e�{�[���̃O���[�o���i���݂́j�|�[�Y�s���񋟂��ꂽ�x�N�^�[�ɏ[�U�B
	// ���Ԃ�0.0f�ȏ��mDuration�ȉ��ł��邱�ƁB
	void GetGlobalPoseAtTime(std::vector<Matrix4>& outPoses, const class Skeleton* inSkeleton, float inTime) const;

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
	size_t									mNumBones;
	// �A�j���[�V�����̃t���[����
	size_t									mNumFrames;
	// �A�j���[�V�����̎������ԁi�b�j
	float									mDuration;
	// �A�j���[�V�����ɂ�����e�t���[���̎�������
	float									mFrameDuration;
	// �g���b�N��̊e�t���[���ɑ΂������ϊ��B
	// �O���̃x�N�g���̊e�C���f�b�N�X�͍��ł���A
	// �����̃x�N�g���̓t���[���ł��B
	std::vector<std::vector<BoneTransform>> mTracks;

	class Skeleton*							mSkeleton;
	//�A�j���[�V���������[�v�����邽�߂̃t���O
	bool									isLoop;
	//�A�j���[�V�������Đ��I���������ǂ���
	bool									isAnimationEnd;
};