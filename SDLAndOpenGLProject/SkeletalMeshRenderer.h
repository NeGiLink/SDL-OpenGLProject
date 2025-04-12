#pragma once
#include "MeshRenderer.h"
#include "MatrixPalette.h"
#include "Animation.h"
#include "Skeleton.h"

class SkeletalMeshRenderer : public MeshRenderer
{
public:
	SkeletalMeshRenderer(class ActorObject* owner);
	// �X�P���^�����f���̕`��
	void Draw(class Shader* shader) override;

	void Update(float deltaTime) override;

	// Setters
	void SetSkeleton(class Skeleton* sk) { mSkeleton = sk; }

	class Skeleton* GetSkeleton() { return mSkeleton; }

	// �A�j���[�V�������Đ����܂��B
	// �A�j���[�V�����̒�����Ԃ��܂��B
	float PlayAnimation(const class Animation* anim, float playRate = 1.0f);

	const std::vector<class Animation*> GetAnimations() { return mAnimations;}

	void SetAnimation(class Animation* anim)
	{
		Animation* animation = anim;
		animation->SetSkeleton(mSkeleton);
		mAnimations.push_back(anim);
	}

protected:
	void ComputeMatrixPalette();

	MatrixPalette					mPalette;
	class Skeleton*					mSkeleton;
	const class Animation*			mAnimation;

	std::vector<class Animation*>	mAnimations;

	float							mAnimPlayRate;
	float							mAnimTime;
};