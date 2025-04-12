#pragma once
#include "Animation.h"
#include <vector>

//複数個あるアニメーションを管理するクラス
//Unityの「Animator」を意識して設計
class Animator
{
public:

	bool Load(const std::string& fileName);

	std::vector<Animation*> GetAnimations() { return mAnimations; }

	void SetSkeleton(class Skeleton* skeleton) { mSkeleton = skeleton; }

	
private:

	std::vector<Animation*> mAnimations;

	class Skeleton*			mSkeleton;
};

