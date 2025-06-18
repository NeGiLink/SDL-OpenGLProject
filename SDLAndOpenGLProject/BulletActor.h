#pragma once
#include "MeshActor.h"
#include "SphereCollider.h"
#include "BoxCollider.h"

class BulletActor : public ActorObject
{
private:
	MeshActor*				mBullet;

	Vector3					mPowerDirection;

	SphereCollider*			mSphereCollider;

	BoxCollider*			mBoxCollider;

	float					mDestroyCount;

	float					mPower;
public:
							BulletActor(Vector3 powerDir,Vector3 position);
							~BulletActor();

	void					UpdateActor(float deltaTime) override;

	void					OnCollisionEnter(class ActorObject* target) override;
};

