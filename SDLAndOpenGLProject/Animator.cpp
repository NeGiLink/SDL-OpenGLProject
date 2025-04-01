#include "Animator.h"

bool Animator::Load(const std::string& fileName)
{
	Animation* anim = new Animation(mSkeleton);

	if (!anim->Load(fileName)) {
		return false;
	}

	mAnimations.push_back(anim);
	return true;
}
