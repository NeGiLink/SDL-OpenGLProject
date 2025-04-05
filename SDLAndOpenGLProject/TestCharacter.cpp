#include "TestCharacter.h"
#include "Mesh.h"
#include "SkeletalMeshRenderer.h"
#include "Animator.h"
#include "WinMain.h"
#include "BaseScene.h"
#include "Renderer.h"
#include "BoxComponent.h"

TestCharacter::TestCharacter(BaseScene* game)
	:ActorObject(game)
{
	SetPosition(Vector3(0.0f, -100.0f, 0.0f));
	animator = new Animator();
	GetGame()->GetAnimator(animatorName, animator);
	mMeshComp = new SkeletalMeshRenderer(this);
	mMeshComp->SetMeshs(game->GetWinMain()->GetRenderer()->GetMeshs("Paladin J Nordstrom.fbx"));
	mMeshComp->SetSkeleton(GetGame()->GetSkeleton("Assets/Models/Paladin J Nordstrom.fbx"));
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
