#include "TPSPlayer.h"

TPSPlayer::TPSPlayer()
	:ActorObject()
{
	mSkeletonMeshActor = new SkeletonMeshActor();
	mSkeletonMeshActor->Load("Y Bot.fbx");
	//アニメーションの読み込み
	mSkeletonMeshActor->SetAnimatorName("TPSPlayer");
	mSkeletonMeshActor->GetAnimator()->Load("Sword And Shield Idle.fbx", true, true);
	mSkeletonMeshActor->GetAnimator()->Load("Running.fbx", true, true);
	mSkeletonMeshActor->GetAnimator()->Load("Jumping.fbx", false, false);
	mSkeletonMeshActor->GetAnimator()->Load("Jump.fbx", false, false);
	mSkeletonMeshActor->GetAnimator()->Load("Capoeira.fbx", true);
	mSkeletonMeshActor->GetAnimator()->Load("T-Pose.fbx", true);

	mSkeletonMeshActor->GetAnimator()->PlayAnimation(mSkeletonMeshActor->GetAnimator()->GetAnimations()[State::TPose]);
	
	//スケルトンメッシュを子オブジェクトに設定
	AddChildActor(mSkeletonMeshActor);
	mSkeletonMeshActor->SetLocalPosition(Vector3::Zero);
	mSkeletonMeshActor->SetLocalRotation(Quaternion());


	mFollowCamera = new FollowCamera(this);

	mMovement = new FollowObjectMovement(this);

	mRigidbody = new Rigidbody(this);
	mRigidbody->SetSolverIterationCount(6);

	// ボックスの当たり判定の機能を追加
	mBoxCollider = new BoxCollider(this);
	AABB myBox(Vector3(-0.5f, 0.0f, -0.5f), Vector3(0.5f, 2.0f, 0.5f));
	mBoxCollider->SetObjectBox(myBox);
	mBoxCollider->SetShouldRotate(false);
	mBoxCollider->SetStaticObject(false);
}

void TPSPlayer::UpdateActor(float deltaTime)
{
	if (!mMovement->IsJumping())
	{
		if (mMovement->GetInputDirection().Length() > 0)
		{
			mSkeletonMeshActor->GetAnimator()->PlayBlendAnimation(mSkeletonMeshActor->GetAnimator()->GetAnimations()[State::Run]);
		}
		else if (mMovement->GetInputDirection().Length() <= 0)
		{
			mSkeletonMeshActor->GetAnimator()->PlayBlendAnimation(mSkeletonMeshActor->GetAnimator()->GetAnimations()[State::Idle]);
		}
	}

	mMovement->SetJumping(true);
	// Make a line segment
	const float cAimDist = 1.5f;
	Vector3 start = mPosition;
	start.y += 0.5f;
	Vector3 dir = GetUp();
	dir *= -1;
	LineSegment l(start, start + dir * cAimDist);
	// Segment cast
	PhysWorld::CollisionInfo info;
	if (mGame->GetPhysWorld()->RayCast(l, info))
	{
		if (info.mActor->GetActorTag() == ActorTag::Ground)
		{
			mMovement->SetJumping(false);
			Debug::Log("In Ground");
		}
		else
		{
			Debug::Log("Out Ground");
		}
	}
	else
	{
		Debug::Log("Out Ground");
	}
}

void TPSPlayer::ActorInput(const InputState& keys)
{
	if (keys.Keyboard.GetKeyDown(SDL_SCANCODE_SPACE) && !mMovement->IsJumping())
	{
		mSkeletonMeshActor->GetAnimator()->PlayBlendAnimation(mSkeletonMeshActor->GetAnimator()->GetAnimations()[State::RunJump]);
	}
	mMovement->MoveInputUpdate(keys);
}
