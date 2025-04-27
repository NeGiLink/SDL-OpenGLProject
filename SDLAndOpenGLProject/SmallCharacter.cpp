#include "SmallCharacter.h"


SmallCharacter::SmallCharacter()
	:ActorObject()
{
	SetPosition(Vector3(-4.0f, -1.0f, 0.0f));
	animator = new Animator();
	GetGame()->GetAnimator(animatorName, animator);
	mMeshComp = new SkeletalMeshRenderer(this);
	mMeshComp->SetMeshs(GetGame()->GetWinMain()->GetRenderer()->GetMeshs("goblin_d_shareyko.fbx"));
	mMeshComp->SetSkeleton(GetGame()->GetSkeleton("Assets/Models/goblin_d_shareyko.fbx"),this);
	mMeshComp->SetAnimator(animator);
	animator->SetSkeleton(mMeshComp->GetSkeleton());
	animator->Load("Assets/Idle.fbx",true);
	animator->Load("Assets/Running.fbx",true);
	animator->Load("Assets/Jumping.fbx");
	animator->Load("Assets/Capoeira.fbx",true);
	animator->Load("Assets/T-Pose.fbx",true);
	animator->PlayAnimation(animator->GetAnimations()[State::TPose]);

	//mSword = new Sword(game);
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
