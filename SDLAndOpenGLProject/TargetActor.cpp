#include "TargetActor.h"

TargetActor::TargetActor()
	:ActorObject()
	, mMesh(nullptr)
	, mHitCoolDownCount(0)
	, mRotateCount(2.0f)
{
	mMesh = new MeshActor();
	mMesh->Load("Target.fbx");
	AddChildActor(mMesh);
	
	BoxCollider* box = new BoxCollider(this);
	box->SetObjectBox(mMesh->GetBoxAABB());
	box->SetObjectOBB(mMesh->GetBoxOBB());
	mBoxCollider = box;
}

void TargetActor::RotateTarget()
{
	float x = GetRotationAmountX();
	x += 0.1f;
	Quaternion q = Quaternion(Vector3::UnitX, x);
	SetLocalRotation(q);
	SetRotationAmountX(x);
}

void TargetActor::UpdateActor(float deltaTime)
{
	if (mHitCoolDownCount > 0)
	{
		RotateTarget();

		mHitCoolDownCount -= deltaTime;
	}
	else
	{
		LookAt(mGame->GetPlayer()->GetPosition());
	}
}

void TargetActor::OnCollisionEnter(ActorObject* target)
{
	BulletActor* bullet = (BulletActor*)target;
	if (bullet == nullptr) { return; }
	if (mHitCoolDownCount > 0) { return; }
	mHitCoolDownCount = mRotateCount;

}
