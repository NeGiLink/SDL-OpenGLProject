#include "TestCharacter.h"


TestCharacter::TestCharacter()
	:ActorObject()
{
	animator = new Animator();
	GetGame()->GetAnimator(animatorName, animator);
	mMeshComp = new SkeletalMeshRenderer(this);
	mMeshComp->SetMeshs(GetGame()->GetWinMain()->GetRenderer()->GetMeshs("Paladin J Nordstrom.fbx"));
	mMeshComp->SetSkeleton(GetGame()->GetSkeleton("Assets/Models/Paladin J Nordstrom.fbx"),this);
	mMeshComp->SetAnimator(animator);
	animator->SetSkeleton(mMeshComp->GetSkeleton());
	animator->Load("Assets/Idle.fbx",true);
	animator->Load("Assets/Running.fbx",true);
	animator->Load("Assets/Jumping.fbx");
	animator->Load("Assets/Capoeira.fbx",true);
	animator->Load("Assets/T-Pose.fbx",true);
	animator->PlayAnimation(animator->GetAnimations()[State::TPose]);
}

void TestCharacter::ActorInput(const struct InputState& keys)
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
