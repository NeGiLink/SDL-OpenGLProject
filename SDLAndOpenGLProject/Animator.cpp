#include "Animator.h"

/// <summary>
/// アニメーションを読み込む処理
/// </summary>
/// <param name="fileName">
/// アニメーションのファイル名
/// </param>
/// <param name="animLoop">
/// アニメーションのループ設定
/// </param>
/// <returns></returns>
bool Animator::Load(const std::string& fileName,bool animLoop)
{
	Animation* anim = new Animation(mSkeleton);

	if (!anim->Load(fileName)) {
		return false;
	}
	anim->SetLoop(animLoop);
	mAnimations.push_back(anim);
	return true;
}
