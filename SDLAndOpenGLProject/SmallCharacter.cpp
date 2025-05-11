#include "SmallCharacter.h"


SmallCharacter::SmallCharacter()
	:ActorObject()
{
	animator = new Animator();
	
	GetGame()->GetAnimator(animatorName, animator);

	mSkeletonMesh = new SkeletalMeshRenderer(this);
	
	mSkeletonMesh->LoadSkeletonMesh("goblin_d_shareyko.fbx", this);
	
	mSkeletonMesh->SetAnimator(animator);
	
	animator->SetSkeleton(mSkeletonMesh->GetSkeleton());
	
	animator->Load("Idle.fbx",true);
	animator->Load("Running.fbx",true);
	animator->Load("Jumping.fbx");
	animator->Load("Capoeira.fbx",true);
	animator->Load("T-Pose.fbx",true);
	animator->PlayAnimation(animator->GetAnimations()[State::TPose]);
}

void SmallCharacter::ActorInput(const struct InputState& keys)
{
	if (keys.Keyboard.GetKeyDown(SDL_SCANCODE_1))
	{
		animator->PlayBlendAnimation(animator->GetAnimations()[State::TPose]);
	}
	else if (keys.Keyboard.GetKeyDown(SDL_SCANCODE_2))
	{
		animator->PlayBlendAnimation(animator->GetAnimations()[State::Idle]);
	}
	else if (keys.Keyboard.GetKeyDown(SDL_SCANCODE_3))
	{
		animator->PlayBlendAnimation(animator->GetAnimations()[State::Run]);
	}
	else if (keys.Keyboard.GetKeyDown(SDL_SCANCODE_4))
	{
		animator->PlayBlendAnimation(animator->GetAnimations()[State::Jump]);
	}
	else if (keys.Keyboard.GetKeyDown(SDL_SCANCODE_5))
	{
		animator->PlayBlendAnimation(animator->GetAnimations()[State::Capoeira]);
	}
}
