#pragma once
#include "StandardLibrary.h"
#include "Math.h"
#include "Collision.h"

#include "Component.h"
#include "Actor.h"
#include "BaseScene.h"
#include "PhysWorld.h"

class Rigidbody : public Component
{
public:
	Rigidbody(class ActorObject* owner, int updateOrder = 100);

	void FixedUpdate(float deltaTime)override;
	void AddForce(Vector3 velocity);
private:
	bool	mUseGravity;

	float	mGravityScale;

	float	mMass;

	Vector3 mVelocity;
};

