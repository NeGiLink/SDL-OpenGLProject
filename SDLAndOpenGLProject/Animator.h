#pragma once
#include "MatrixPalette.h"
#include "Animation.h"
#include "Skeleton.h"

//複数個あるアニメーションを管理するクラス
//Unityの「Animator」を意識して設計
class Animator
{
public:
	//アニメーション読み込み処理
	bool Load(const std::string& fileName,bool animLoop = 0);

	void Update(float deltaTime);

	void SetSkeleton(class Skeleton* skeleton) { mSkeleton = skeleton; }

	// アニメーションを再生します。
	// アニメーションの長さを返します。
	float PlayAnimation(class Animation* anim, float playRate = 1.0f);

	float PlayBlendAnimation(class Animation* anim, float playRate = 1.0f, float blendTime = 0.5f);

	void ComputeMatrixPalette();

	void BlendComputeMatrixPalette();


	MatrixPalette GetPalette() { return mPalette; }

	std::vector<Animation*> GetAnimations() { return mAnimations; }

	class Skeleton* GetSkeleton() { return mSkeleton; }

	class Animation* GetAnimation() { return mAnimation; }

	class Animation* GetBlendAnimation() { return mBlendAnimation; }
	//アニメーションの倍率
	float							GetAnimPlayRate() { return mAnimPlayRate; }
	//現在再生中のアニメーションの時間
	float							GetAnimTime() { return mAnimTime; }
	//ブレンドアニメーションの時間
	float							GetBlendAnimTime() { return mBlendAnimTime; }
	// 現在のブレンド経過時間
	float							GetBlendElapsed() { return mBlendElapsed; }
	//アニメーションのブレンドを行うためのフラグ
	bool							IsBlending() { return blending; }
private:

	MatrixPalette					mPalette;

	//アニメーションを配列で持ってる変数
	std::vector<Animation*>			mAnimations;

	class Skeleton*					mSkeleton;

	class Animation*				mAnimation;

	class Animation*				mBlendAnimation;
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

