#include "SmallCharacter.h"
#include "Mesh.h"
#include "SkeletalMeshRenderer.h"
#include "Animator.h"
#include "WinMain.h"
#include "BaseScene.h"
#include "Renderer.h"
#include "BoxCollider.h"
#include "Sword.h"

SmallCharacter::SmallCharacter(BaseScene* game)
	:ActorObject(game)
{
	SetPosition(Vector3(-400.0f, -100.0f, 0.0f));
	animator = new Animator();
	GetGame()->GetAnimator(animatorName, animator);
	mMeshComp = new SkeletalMeshRenderer(this);
	mMeshComp->SetMeshs(game->GetWinMain()->GetRenderer()->GetMeshs("goblin_d_shareyko.fbx"));
	mMeshComp->SetSkeleton(GetGame()->GetSkeleton("Assets/Models/goblin_d_shareyko.fbx"));
	animator->SetSkeleton(mMeshComp->GetSkeleton());
	animator->Load("Assets/Idle.fbx",true);
	animator->Load("Assets/Running.fbx",true);
	animator->Load("Assets/Jumping.fbx");
	animator->Load("Assets/Capoeira.fbx",true);
	animator->Load("Assets/T-Pose.fbx",true);
	mMeshComp->PlayAnimation(animator->GetAnimations()[State::TPose]);

	//mSword = new Sword(game);
}

void SmallCharacter::ActorInput(const struct InputState& keys)
{
	if (keys.Keyboard.GetKeyDown(SDL_SCANCODE_1))
	{
		mMeshComp->PlayBlendAnimation(animator->GetAnimations()[State::TPose]);
	}
	else if (keys.Keyboard.GetKeyDown(SDL_SCANCODE_2))
	{
		mMeshComp->PlayBlendAnimation(animator->GetAnimations()[State::Idle]);
	}
	else if (keys.Keyboard.GetKeyDown(SDL_SCANCODE_3))
	{
		mMeshComp->PlayBlendAnimation(animator->GetAnimations()[State::Run]);
	}
	else if (keys.Keyboard.GetKeyDown(SDL_SCANCODE_4))
	{
		mMeshComp->PlayBlendAnimation(animator->GetAnimations()[State::Jump]);
	}
	else if (keys.Keyboard.GetKeyDown(SDL_SCANCODE_5))
	{
		mMeshComp->PlayBlendAnimation(animator->GetAnimations()[State::Capoeira]);
	}
}

void SmallCharacter::UpdateActor(float deltaTime)
{
	/*
	Matrix4 mat = mMeshComp->GetSkeleton()->GetBonePosition("RightHand");
	Vector3 pos = mPosition + mat.GetTranslation();
	mSword->SetPosition(pos);
	Quaternion r = mat.GetRotation();
	r.RotateByAxisAngle(Vector3::UnitX, 240);
	r.RotateByAxisAngle(Vector3::UnitY, -45);
	mSword->SetRotation(r);
	*/
}
