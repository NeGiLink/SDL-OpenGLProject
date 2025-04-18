#pragma once
#include "MeshRenderer.h"
#include "MatrixPalette.h"
#include "Animation.h"
#include "Skeleton.h"

class SkeletalMeshRenderer : public MeshRenderer
{
public:
	SkeletalMeshRenderer(class ActorObject* owner);
	// スケルタルモデルの描画
	void Draw(class Shader* shader) override;

	void Update(float deltaTime) override;

	// Setters
	void SetSkeleton(class Skeleton* sk) { mSkeleton = sk; }

	class Skeleton* GetSkeleton() { return mSkeleton; }

	// アニメーションを再生します。
	// アニメーションの長さを返します。
	float PlayAnimation(class Animation* anim, float playRate = 1.0f);

	float PlayBlendAnimation(class Animation* anim, float playRate = 1.0f,float blendTime = 0.5f);

	const std::vector<class Animation*> GetAnimations() { return mAnimations;}

	void SetAnimation(class Animation* anim)
	{
		Animation* animation = anim;
		animation->SetSkeleton(mSkeleton);
		mAnimations.push_back(anim);
	}

protected:
	void ComputeMatrixPalette();

	void BlendComputeMatrixPalette();

	MatrixPalette					mPalette;

	class Skeleton*					mSkeleton;
	
	class Animation*				mAnimation;
	
	class Animation*				mBlendAnimation;

	std::vector<class Animation*>	mAnimations;
	//アニメーションの倍率
	float							mAnimPlayRate;
	//現在再生中のアニメーションの時間
	float							mAnimTime;
	//ブレンドアニメーションの時間
	float							mBlendAnimTime;
	// 現在のブレンド経過時間
	float							mBlendElapsed = 0.0f;     
	//アニメーションのブレンドを行うためのフラグ
	bool							blending;
};