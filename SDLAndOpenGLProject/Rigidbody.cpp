#include "Rigidbody.h"

Rigidbody::Rigidbody(ActorObject* owner, int updateOrder)
	: Component(owner)
	, mUseGravity(false)
	, mGravityScale(9.81f)
	, mMass(1.0f)
{
	mUseGravity = true;
}

void Rigidbody::FixedUpdate(float deltaTime)
{
	Vector3 position = mOwner->GetPosition();
	Vector3 gravity = Vector3::UnitY * (-mGravityScale);
	position += mVelocity + gravity * deltaTime;
	mOwner->SetPosition(position);
}

void Rigidbody::AddForce(Vector3 force)
{
	Vector3 deltaV = force / mMass;
	mVelocity += deltaV;
}
