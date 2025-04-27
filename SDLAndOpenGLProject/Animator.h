#pragma once
#include "MatrixPalette.h"
#include "Animation.h"
#include "Skeleton.h"

//��������A�j���[�V�������Ǘ�����N���X
//Unity�́uAnimator�v���ӎ����Đ݌v
class Animator
{
public:
	//�A�j���[�V�����ǂݍ��ݏ���
	bool Load(const std::string& fileName,bool animLoop = 0);

	void Update(float deltaTime);

	void SetSkeleton(class Skeleton* skeleton) { mSkeleton = skeleton; }

	// �A�j���[�V�������Đ����܂��B
	// �A�j���[�V�����̒�����Ԃ��܂��B
	float PlayAnimation(class Animation* anim, float playRate = 1.0f);

	float PlayBlendAnimation(class Animation* anim, float playRate = 1.0f, float blendTime = 0.5f);

	void ComputeMatrixPalette();

	void BlendComputeMatrixPalette();


	MatrixPalette GetPalette() { return mPalette; }

	std::vector<Animation*> GetAnimations() { return mAnimations; }

	class Skeleton* GetSkeleton() { return mSkeleton; }

	class Animation* GetAnimation() { return mAnimation; }

	class Animation* GetBlendAnimation() { return mBlendAnimation; }
	//�A�j���[�V�����̔{��
	float							GetAnimPlayRate() { return mAnimPlayRate; }
	//���ݍĐ����̃A�j���[�V�����̎���
	float							GetAnimTime() { return mAnimTime; }
	//�u�����h�A�j���[�V�����̎���
	float							GetBlendAnimTime() { return mBlendAnimTime; }
	// ���݂̃u�����h�o�ߎ���
	float							GetBlendElapsed() { return mBlendElapsed; }
	//�A�j���[�V�����̃u�����h���s�����߂̃t���O
	bool							IsBlending() { return blending; }
private:

	MatrixPalette					mPalette;

	//�A�j���[�V������z��Ŏ����Ă�ϐ�
	std::vector<Animation*>			mAnimations;

	class Skeleton*					mSkeleton;

	class Animation*				mAnimation;

	class Animation*				mBlendAnimation;
	//�A�j���[�V�����̔{��
	float							mAnimPlayRate;
	//���ݍĐ����̃A�j���[�V�����̎���
	float							mAnimTime;
	//�u�����h�A�j���[�V�����̎���
	float							mBlendAnimTime;
	// ���݂̃u�����h�o�ߎ���
	float							mBlendElapsed = 0.0f;
	//�A�j���[�V�����̃u�����h���s�����߂̃t���O
	bool							blending;
};

