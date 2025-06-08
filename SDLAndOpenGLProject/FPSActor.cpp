#include "FPSActor.h"
#include "HUD.h"

FPSActor::FPSActor()
	:ActorObject()
{
	mBasicInput = new BasicInputAction(this);

	mRigidbody = new Rigidbody(this);
	mRigidbody->SetSolverIterationCount(6);
	mRigidbody->SetBounciness(0.5f);

	mAudioComp = new AudioComponent(this);
	mLastFootstep = 0.0f;
	mFootstep = mAudioComp->LoadAudio("event:/Footstep");
	mFootstep.SetPaused(true);

	mFPSCamera = new FPSCamera(this);

	// ボックスの当たり判定の機能を追加
	mBoxCollider = new BoxCollider(this);
	OBB myOBB(mPosition, mRotation, Vector3(1.0f,1.5f,1.0f));
	AABB myBox(Vector3(-0.5f, -1.0f, -0.5f),Vector3(0.5f, 0.5f, 0.5f));
	mBoxCollider->SetObjectBox(myBox);
	mBoxCollider->SetObjectOBB(myOBB);
	mBoxCollider->SetShouldRotate(false);
	mBoxCollider->SetStaticObject(false);

	mMaxHP = 100.0f;
	mHP = mMaxHP;
	//イベント追加
	mEvent.Add
	(
		[this]() 
		{
			mFootstep.SetPaused(false); mFootstep.ResetStart(); 
		}
	);
}

void FPSActor::FixedUpdateActor(float deltaTime){}


void FPSActor::UpdateActor(float deltaTime)
{
	ActorObject::UpdateActor(deltaTime);

	//Debug::Log("x %2f", mPosition.x);
	//Debug::Log("y %2f", mPosition.y);
	//Debug::Log("z %2f", mPosition.z);

	if (!mBasicInput->GetJumping()) 
	{
		// 足音のSEを再生する処理
		mLastFootstep -= deltaTime;
		if ((!Math::NearZero(mBasicInput->GetForwardSpeed()) ||
			!Math::NearZero(mBasicInput->GetStrafeSpeed())) &&
			mLastFootstep <= 0.0f)
		{
			mEvent.Invoke();
			mLastFootstep = 0.5f;
		}
	}

	mBasicInput->SetJumping(true);
	// Make a line segment
	const float cAimDist = 3.0f;
	Vector3 start = mPosition;
	//start.y += 0.5f;
	Vector3 dir = GetUp();
	dir *= -1;
	LineSegment l(start, start + dir * cAimDist);
	// Segment cast
	PhysWorld::CollisionInfo info;
	ActorTag tag = ActorTag::Ground;
	if (mGame->GetPhysWorld()->RayCast(l, info,tag))
	{
		if (info.mActor->GetActorTag() == ActorTag::Ground)
		{
			mBasicInput->SetJumping(false);
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

void FPSActor::ActorInput(const struct InputState& keys)
{
	mBasicInput->MoveInputUpdate(keys);
	mFPSCamera->CameraInputUpdate();
}

void FPSActor::SetFootstepSurface(float value)
{
	//ここで一時停止します。
	// FMODでパラメーターを設定した方法を変更すると、足音が再生されるため
	mFootstep.SetPaused(true);
	mFootstep.SetParameter("Surface", value);
}

void FPSActor::SetVisible(bool visible)
{
	mMeshComp->SetVisible(visible);
}
void FPSActor::OnCollisionEnter(ActorObject* target)
{
	if (target->GetActorTag() == ActorTag::Enemy)
	{
		mHP -= 10.0f;
		if (mHP < 0)
		{
			mHP = 0;
		}
		mGame->GetHUD()->GetHelthBar()->SetFillAmount(mHP / mMaxHP);
	}
	else if (target->GetActorTag() == ActorTag::Recovery)
	{
		mHP += 10.0f;
		if (mHP > mMaxHP)
		{
			mHP = mMaxHP;
		}
		mGame->GetHUD()->GetHelthBar()->SetFillAmount(mHP / mMaxHP);
	}
}

void FPSActor::OnCollisionExit(ActorObject* target)
{

}
