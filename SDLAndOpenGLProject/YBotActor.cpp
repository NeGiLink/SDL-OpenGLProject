#include "YBotActor.h"
#include "Mesh.h"
#include "SkeletalMeshRenderer.h"
#include "Animator.h"
#include "WinMain.h"
#include "BaseScene.h"
#include "Renderer.h"
#include "BoxCollider.h"
#include "Sword.h"

YBotActor::YBotActor(BaseScene* game)
	:ActorObject(game)
{
	SetPosition(Vector3(200.0f, -100.0f, 0.0f));
	animator = new Animator();
	GetGame()->GetAnimator(animatorName, animator);
	mSkeletonMesh = new SkeletalMeshRenderer(this);
	mSkeletonMesh->SetMeshs(game->GetWinMain()->GetRenderer()->GetMeshs("Y Bot.fbx"));
	mSkeletonMesh->SetSkeleton(GetGame()->GetSkeleton("Assets/Models/Y Bot.fbx"));
	animator->SetSkeleton(mSkeletonMesh->GetSkeleton());
	animator->Load("Assets/Idle.fbx",true);
	animator->Load("Assets/Running.fbx",true);
	animator->Load("Assets/Jumping.fbx");
	animator->Load("Assets/Capoeira.fbx",true);
	animator->Load("Assets/T-Pose.fbx",true);
	mSkeletonMesh->PlayAnimation(animator->GetAnimations()[State::TPose]);

	mSword = new Sword(game);
	/*
	mSword->SetRotationAmountX(0);
	mSword->SetRotationAmountY(-Math::PiOver2);
	mSword->SetRotationAmountZ(Math::PiOver2);
	*/
}

void YBotActor::ActorInput(const struct InputState& keys)
{
	if (keys.Keyboard.GetKeyDown(SDL_SCANCODE_1))
	{
		mSkeletonMesh->PlayBlendAnimation(animator->GetAnimations()[State::TPose]);
	}
	else if (keys.Keyboard.GetKeyDown(SDL_SCANCODE_2))
	{
		mSkeletonMesh->PlayBlendAnimation(animator->GetAnimations()[State::Idle]);
	}
	else if (keys.Keyboard.GetKeyDown(SDL_SCANCODE_3))
	{
		mSkeletonMesh->PlayBlendAnimation(animator->GetAnimations()[State::Run]);
	}
	else if (keys.Keyboard.GetKeyDown(SDL_SCANCODE_4))
	{
		mSkeletonMesh->PlayBlendAnimation(animator->GetAnimations()[State::Jump]);
	}
	else if (keys.Keyboard.GetKeyDown(SDL_SCANCODE_5))
	{
		mSkeletonMesh->PlayBlendAnimation(animator->GetAnimations()[State::Capoeira]);
	}
}

void YBotActor::UpdateActor(float deltaTime)
{
	mSword->LocalBonePositionUpdateActor(mSkeletonMesh->GetSkeleton()->GetBonePosition("RightHand"),this->GetWorldTransform());
}
