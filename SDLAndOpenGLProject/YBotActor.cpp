#include "YBotActor.h"

YBotActor::YBotActor()
	:ActorObject()
{
	mFollowCamera = new FollowCamera(this);

	mMovement = new FollowObjectMovement(this);

	mRigidbody = new Rigidbody(this);

	animator = new Animator();
	
	GetGame()->GetAnimator(animatorName, animator);
	
	//SkeletalMeshRenderer生成
	mSkeletonMesh = new SkeletalMeshRenderer(this);

	//Meshの読み込み
	//Skeletonの読み込み
	mSkeletonMesh->LoadSkeletonMesh("Y Bot.fbx",this);
	
	mSkeletonMesh->SetAnimator(animator);
	
	//Skeletonデータをアニメーターに設定
	animator->SetSkeleton(mSkeletonMesh->GetSkeleton());
	animator->Load("Sword And Shield Idle.fbx",true,true);
	animator->Load("Running.fbx",true,true);
	animator->Load("Jumping.fbx", false, false);
	animator->Load("Jump.fbx",false, false);
	animator->Load("Capoeira.fbx",true);
	animator->Load("T-Pose.fbx",true);
	animator->PlayAnimation(animator->GetAnimations()[State::TPose]);

	mSword = new Sword();
	mSkeletonMesh->GetSkeleton()->AddBoneChildActor("RightHand", mSword);
	mSword->SetLocalPosition(Vector3());

	// ボックスの当たり判定の機能を追加
	mBoxComp = new BoxCollider(this);
	AABB myBox(Vector3(-0.5f, 0.0f, -0.5f), Vector3(0.5f, 2.0f, 0.5f));
	mBoxComp->SetObjectBox(myBox);
	mBoxComp->SetShouldRotate(false);
	mBoxComp->SetStaticObject(false);
}

void YBotActor::UpdateActor(float deltaTime)
{
	if (!mMovement->IsJumping())
	{
		if (mMovement->GetInputDirection().Length() > 0)
		{
			animator->PlayBlendAnimation(animator->GetAnimations()[State::Run]);
		}
		else if (mMovement->GetInputDirection().Length() <= 0)
		{
			animator->PlayBlendAnimation(animator->GetAnimations()[State::Idle]);
		}
	}

}

void YBotActor::ActorInput(const struct InputState& keys)
{
	if (keys.Keyboard.GetKeyDown(SDL_SCANCODE_E))
	{
		bool active = animator->GetAnimations()[State::RunJump]->IsRootMotion();
		active = !active;
		animator->GetAnimations()[State::RunJump]->SetRootMotion(active);
	}

	if (keys.Keyboard.GetKeyDown(SDL_SCANCODE_SPACE) && !mMovement->IsJumping())
	{
		animator->PlayBlendAnimation(animator->GetAnimations()[State::RunJump]);
	}
	mMovement->MoveInputUpdate(keys);
}

void YBotActor::OnCollisionEnter(ActorObject* target)
{
	if (target->GetActorTag() != ActorTag::Ground) { return; }
	mMovement->SetJumping(false);
}

void YBotActor::OnCollisionExit(ActorObject* target)
{
	if (target->GetActorTag() != ActorTag::Ground) { return; }
	mMovement->SetJumping(true);
}
