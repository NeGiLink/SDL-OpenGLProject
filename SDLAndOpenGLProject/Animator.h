#pragma once
#include "MatrixPalette.h"
#include "Animation.h"
#include "Skeleton.h"

/*
* ===�G���W����������/Engine internal processing===
*/

//��������A�j���[�V�������Ǘ�����N���X
//Unity�́uAnimator�v���ӎ����Đ݌v
//�A�j���[�V�����̍Đ��A�u�����h�Ȃǂ��s��
class Animator
{
public:
	//�A�j���[�V�����ǂݍ��ݏ���
	bool							Load(const string& fileName,bool animLoop = 0,bool rootMotion = 0);

	void							Update(float deltaTime);

	void							SetSkeleton(class Skeleton* skeleton);

	// �A�j���[�V�������Đ����܂��B
	// �A�j���[�V�����̒�����Ԃ��܂��B
	float							PlayAnimation(class Animation* anim, float playRate = 1.0f);

	float							PlayBlendAnimation(class Animation* anim, float playRate = 1.0f, float blendTime = 0.25f);
	//�X�P���g���ƃA�j���[�V�������g���ăX�L�j���O�s��ipalette�j�ƃ{�[���̉����X�V���s��
	void							ComputeMatrixPalette();

	void							BlendComputeMatrixPalette();

	//Getter
	MatrixPalette&					GetPalette() { return mPalette; }

	vector<Animation*>				GetAnimations() { return mAnimations; }

	class Skeleton*					GetSkeleton() { return mSkeleton; }

	class Animation*				GetAnimation() { return mAnimation; }

	class Animation*				GetBlendAnimation() { return mBlendAnimation; }
	//�A�j���[�V�����̔{��
	float							GetAnimPlayRate() { return mAnimPlayRate; }
	//���ݍĐ����̃A�j���[�V�����̎���
	float							GetAnimTime() { return mAnimTime; }
	//�u�����h�A�j���[�V�����̎���
	float							GetBlendAnimTime() { return mBlendAnimTime; }
	// ���݂̃u�����h�o�ߎ���
	float							GetBlendElapsed() { return mBlendElapsed; }
	//���݂̃A�j���[�V�����̎��Ԃ𐳋K�������l���o�͂���֐�
	float							GetNormalizedTime();
	//Setter
	//�A�j���[�V�����̃u�����h���s�����߂̃t���O
	bool							IsBlending() { return mBlending; }
private:

	MatrixPalette					mPalette;

	//�A�j���[�V������z��Ŏ����Ă�ϐ�
	vector<Animation*>				mAnimations;

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
	bool							mBlending;
};

