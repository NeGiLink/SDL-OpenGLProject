#pragma once
#include "MeshActor.h"
#include "BoxCollider.h"
#include "BulletActor.h"

class TargetActor : public ActorObject
{
private:
	MeshActor*		mMesh;

	BoxCollider*	mBoxCollider;

	float			mHitCoolDownCount;

	float			mRotateCount;
public:
	TargetActor();

	void RotateTarget();

	void UpdateActor(float deltaTime)override;

	void OnCollisionEnter(class ActorObject* target) override;
};

