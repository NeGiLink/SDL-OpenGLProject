#include "FollowActor.h"
#include "SkeletalMeshRenderer.h"
#include "WinMain.h"
#include "BaseScene.h"
#include "Renderer.h"
#include "FollowCamera.h"
#include "MoveComponent.h"
#include "Animator.h"

FollowActor::FollowActor(BaseScene* game)
	:ActorObject(game)
	, mMoving(false)
{
	animator = new Animator();
	GetGame()->GetAnimator(animatorName, animator);
	mMeshComp = new SkeletalMeshRenderer(this);
	mMeshComp->SetMesh(game->GetWinMain()->GetRenderer()->GetMesh("Assets/CatWarrior.gpmesh"));
	mMeshComp->SetSkeleton(GetGame()->GetSkeleton("Assets/CatWarrior.gpskel"));
	animator->SetSkeleton(mMeshComp->GetSkeleton());
	animator->Load("Assets/CatActionIdle.gpanim");
	animator->Load("Assets/CatRunSprint.gpanim");

	mMeshComp->PlayAnimation(animator->GetAnimations()[State::Idle]);
	SetPosition(Vector3(0.0f, 0.0f, -100.0f));

	mMoveComp = new MoveComponent(this);
	mCameraComp = new FollowCamera(this);
	mCameraComp->SnapToIdeal();
}

void FollowActor::ActorInput(const bool* keys)
{
	float forwardSpeed = 0.0f;
	float angularSpeed = 0.0f;
	// wasd movement
	if (keys[SDL_SCANCODE_W])
	{
		forwardSpeed += 400.0f;
	}
	if (keys[SDL_SCANCODE_S])
	{
		forwardSpeed -= 400.0f;
	}
	if (keys[SDL_SCANCODE_A])
	{
		angularSpeed -= Math::Pi;
	}
	if (keys[SDL_SCANCODE_D])
	{
		angularSpeed += Math::Pi;
	}

	// Did we just start moving?
	if (!mMoving && !Math::NearZero(forwardSpeed))
	{
		mMoving = true;
		mMeshComp->PlayAnimation(animator->GetAnimations()[State::Run], 1.25f);
	}
	// Or did we just stop moving?
	else if (mMoving && Math::NearZero(forwardSpeed))
	{
		mMoving = false;
		mMeshComp->PlayAnimation(animator->GetAnimations()[State::Idle]);
	}
	mMoveComp->SetForwardSpeed(forwardSpeed);
	mMoveComp->SetAngularSpeed(angularSpeed);
}

void FollowActor::SetVisible(bool visible)
{
	mMeshComp->SetVisible(visible);
}