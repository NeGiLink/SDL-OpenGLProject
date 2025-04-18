#include "Animator.h"

/// <summary>
/// �A�j���[�V������ǂݍ��ޏ���
/// </summary>
/// <param name="fileName">
/// �A�j���[�V�����̃t�@�C����
/// </param>
/// <param name="animLoop">
/// �A�j���[�V�����̃��[�v�ݒ�
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
