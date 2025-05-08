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
	animator->Load("Assets/Sword And Shield Idle.fbx",true);
	animator->Load("Assets/Running.fbx",true);
	animator->Load("Assets/Jumping.fbx");
	animator->Load("Assets/Capoeira.fbx",true);
	animator->Load("Assets/T-Pose.fbx",true);
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
	if (mMovement->GetInputDirection().Length() > 0)
	{
		animator->PlayBlendAnimation(animator->GetAnimations()[State::Run]);
	}
	else if (mMovement->GetInputDirection().Length() <= 0)
	{
		animator->PlayBlendAnimation(animator->GetAnimations()[State::Idle]);
	}
}

void YBotActor::ActorInput(const struct InputState& keys)
{
	/*
	if (keys.Keyboard.GetKeyDown(KEY_1))
	{
		animator->PlayBlendAnimation(animator->GetAnimations()[State::TPose]);
	}
	else if (keys.Keyboard.GetKeyDown(KEY_2))
	{
		animator->PlayBlendAnimation(animator->GetAnimations()[State::Idle]);
	}
	else if (keys.Keyboard.GetKeyDown(KEY_3))
	{
		animator->PlayBlendAnimation(animator->GetAnimations()[State::Run]);
	}
	else if (keys.Keyboard.GetKeyDown(KEY_4))
	{
		animator->PlayBlendAnimation(animator->GetAnimations()[State::Jump]);
	}
	else if (keys.Keyboard.GetKeyDown(KEY_5))
	{
		animator->PlayBlendAnimation(animator->GetAnimations()[State::Capoeira]);
	}

	Vector3 pos = mLocalPosition;
	if (keys.Keyboard.GetKey(KEY_RIGHT))
	{
		pos.x += 0.01f;
	}
	if (keys.Keyboard.GetKey(KEY_LEFT))
	{
		pos.x -= 0.01f;
	}
	SetLocalPosition(pos);

	Quaternion q = mLocalRotation;
	if (keys.Keyboard.GetKey(KEY_X))
	{
		if (keys.Keyboard.GetKey(KEY_LSHIFT))
		{
			mRotationAmountY += 0.01f;
		}
		else
		{
			mRotationAmountY -= 0.01f;
		}
	}
	q = Quaternion(Vector3::UnitY, mRotationAmountY);
	SetLocalRotation(q);
	*/
	mMovement->MoveInputUpdate(keys);
}
