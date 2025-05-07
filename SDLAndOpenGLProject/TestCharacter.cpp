#include "TestCharacter.h"


TestCharacter::TestCharacter()
	:ActorObject()
{

	mFollowCamera = new FollowCamera(this);

	mMovement = new FollowObjectMovement(this);

	mRigidbody = new Rigidbody(this);

	animator = new Animator();
	
	GetGame()->GetAnimator(animatorName, animator);
	
	mSkeletonMesh = new SkeletalMeshRenderer(this);

	mSkeletonMesh->LoadSkeletonMesh("Paladin J Nordstrom.fbx", this);

	mSkeletonMesh->SetAnimator(animator);
	
	animator->SetSkeleton(mSkeletonMesh->GetSkeleton());
	
	animator->Load("Assets/Idle.fbx",true);
	animator->Load("Assets/Running.fbx",true);
	animator->Load("Assets/Jumping.fbx");
	animator->Load("Assets/Capoeira.fbx",true);
	animator->Load("Assets/T-Pose.fbx",true);
	animator->PlayAnimation(animator->GetAnimations()[State::TPose]);

	// ボックスの当たり判定の機能を追加
	mBoxComp = new BoxCollider(this);
	AABB myBox(Vector3(-0.5f, 0.0f, -0.5f), Vector3(0.5f, 2.0f, 0.5f));
	mBoxComp->SetObjectBox(myBox);
	mBoxComp->SetShouldRotate(false);
	mBoxComp->SetStaticObject(false);
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

	mMovement->MoveInputUpdate(keys);
}
