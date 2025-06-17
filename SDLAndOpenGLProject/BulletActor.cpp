#include "BulletActor.h"

BulletActor::BulletActor(Vector3 powerDir, Vector3 position)
	:ActorObject()
	, mPowerDirection(powerDir)
{
	mBullet = new MeshActor();
	mBullet->Load("Sphere.fbx");
	AddChildActor(mBullet);
	mBullet->SetLocalPosition(Vector3::Zero);
	mBullet->SetLocalScale(Vector3(0.25f, 0.25f, 0.25f));

	BoxCollider* box = new BoxCollider(this);
	box->SetObjectBox(mBullet->GetBoxAABB());
	box->SetObjectOBB(mBullet->GetBoxOBB());
	box->SetCollider(false);
	box->SetStaticObject(false);
	mBoxCollider = box;

	SetLocalPosition(position);

	mRigidbody = new Rigidbody(this);
	mRigidbody->SetUseGravity(false);
	mRigidbody->AddForce(mPowerDirection * 10000.0f);

	mDestroyCount = 3.0f;
}

BulletActor::~BulletActor()
{
	mBullet->SetState(State::EDead);
}

void BulletActor::UpdateActor(float deltaTime)
{
	mDestroyCount -= deltaTime;
	if (mDestroyCount < 0)
	{
		mState = State::EDead;
	}
}

void BulletActor::OnCollisionEnter(ActorObject* target)
{
	if (target->GetActorTag() == ActorTag::Player) { return; }
	mState = State::EDead;
}
