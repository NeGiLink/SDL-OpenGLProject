#pragma once
#include "BoneTransform.h"
#include "Assimp.h"
#include "SDL3.h"

struct AnimationBinHeader 
{
	uint32_t	version = 1;
	float		duration;
	uint32_t	numFrames;
	uint32_t	numBones;
};

struct AnimationBinTransform 
{
	Vector3		position;
	Quaternion	rotation;
	Vector3		scale;
};

//�A�j���[�V����1�̏������N���X
class Animation
{
public:
											Animation(class Skeleton* skeleton);

	bool									Load(const string& fileName);

	bool									ReLoad();

	bool									LoadFromBinary(const std::string& filePath);

	bool									SaveToBinary(const std::string& filePath);

	void									Update();

	size_t									GetNumBones() const { return mNumBones; }
	
	size_t									GetNumFrames() const { return mNumFrames; }
	
	float									GetDuration() const { return mDuration; }
	
	float									GetFrameDuration() const { return mFrameDuration; }

	void									SetSkeleton(class Skeleton* skeleton) { mSkeleton = skeleton; }

	bool									IsLoop() const { return isLoop; }

	void									SetLoop(bool loop) { isLoop = loop; }

	bool									IsAnimationEnd() const { return isAnimationEnd; }

	void									SetIsAnimationEnd(bool animationEnd) { isAnimationEnd = animationEnd; }

	bool									IsRootMotion()const { return isRootMotion; }

	void									SetRootMotion(bool active) 
	{
		isRootMotion = active; 
		isReLoad = true;
	}
	void									SetIsRootMotion(bool x,bool y,bool z)
	{
		isRootMotionX = x;
		isRootMotionY = y;
		isRootMotionZ = z;
		isReLoad = true;
	}

	float									GetRootMotionX() { return mRootMotionX; }
	float									GetRootMotionY() { return mRootMotionY; }
	float									GetRootMotionZ() { return mRootMotionZ; }

	void									SetRootMotionX(float num) 
	{
		mRootMotionX = num; 
		isReLoad = true;
	}
	void									SetRootMotionY(float num) 
	{
		mRootMotionY = num;
		isReLoad = true;
	}
	void									SetRootMotionZ(float num) 
	{
		mRootMotionZ = num; 
		isReLoad = true;
	}
	void									SetRootMotionPosition(Vector3 pos)
	{
		mRootMotionX = pos.x;
		mRootMotionY = pos.y;
		mRootMotionZ = pos.z;
		isReLoad = true;
	}

	// �w�肳�ꂽ�A�j���[�V�����̎��Ԃɂ�����e�{�[���̃O���[�o���i���݂́j�|�[�Y�s���񋟂��ꂽ�x�N�^�[�ɏ[�U�B
	// ���Ԃ�0.0f�ȏ��mDuration�ȉ��ł��邱�ƁB
	void									GetGlobalPoseAtTime(vector<Matrix4>& outPoses, const class Skeleton* inSkeleton, float inTime) const;

private:
	bool									LoadFromJSON(const string& fileName);

	bool									LoadFromFBX(const string& fileName);

	size_t									FindTranslation(float AnimationTime, const aiNodeAnim* pNodeAnim);

	void									CalcInterpolatedTranslation(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim);

	size_t									FindRotation(float AnimationTime, const aiNodeAnim* pNodeAnim);

	void									CalcInterpolatedRotation(aiQuaternion& Out, float AnimationTime, const aiNodeAnim* pNodeAnim);

	size_t									FindScaling(float AnimationTime, const aiNodeAnim* pNodeAnim);

	void									CalcInterpolatedScaling(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim);
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
	vector<vector<BoneTransform>>			mTracks;

	vector<Vector3*>						mRootPosition;

	class Skeleton*							mSkeleton;
	//�A�j���[�V���������[�v�����邽�߂̃t���O
	bool									isLoop;
	//�A�j���[�V�������Đ��I���������ǂ���
	bool									isAnimationEnd;
	//���[�g���[�V�����̃t���O
	bool									isRootMotion;
	bool									isRootMotionX;
	bool									isRootMotionY;
	bool									isRootMotionZ;
	//���[�g���[�V�����̃I�t�Z�b�g
	float									mRootMotionX;
	float									mRootMotionY;
	float									mRootMotionZ;

	bool									isReLoad;

	string									mFileName;

	vector<Vector3>							mRootPositionOffset;
};