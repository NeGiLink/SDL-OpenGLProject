#pragma once
#include "Animation.h"
#include <vector>

//��������A�j���[�V�������Ǘ�����N���X
//Unity�́uAnimator�v���ӎ����Đ݌v
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

