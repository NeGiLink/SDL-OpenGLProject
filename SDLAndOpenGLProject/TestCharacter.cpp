#include "TestCharacter.h"
#include "Mesh.h"
#include "SkeletalMeshComponent.h"
#include "Animator.h"
#include "WinMain.h"
#include "Renderer.h"
#include "BoxComponent.h"

TestCharacter::TestCharacter(WinMain* game)
	:ActorObject(game)
{
	SetPosition(Vector3(0.0f, -100.0f, 0.0f));
	animator = new Animator();
	GetGame()->GetAnimator(animatorName, animator);
	mMeshComp = new SkeletalMeshComponent(this);
	mMeshComp->SetMeshs(GetGame()->GetRenderer()->GetMeshs("Assets/Paladin J Nordstrom.fbx"));
	mMeshComp->SetSkeleton(GetGame()->GetSkeleton("Assets/Paladin J Nordstrom.fbx"));
	animator->SetSkeleton(mMeshComp->GetSkeleton());
	animator->Load("Assets/Idle.fbx");
	animator->Load("Assets/Capoeira.fbx");
	mMeshComp->PlayAnimation(animator->GetAnimations()[State::Capoeira]);
}

void TestCharacter::ActorInput(const bool* keys)
{
	if (keys[SDL_SCANCODE_1])
	{
		mMeshComp->PlayAnimation(animator->GetAnimations()[State::Idle]);
	}
	else if(keys[SDL_SCANCODE_2])
	{
		mMeshComp->PlayAnimation(animator->GetAnimations()[State::Capoeira]);
	}
}
