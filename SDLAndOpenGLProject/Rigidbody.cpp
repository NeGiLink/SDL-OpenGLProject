#include "Rigidbody.h"

Rigidbody::Rigidbody(ActorObject* owner, int updateOrder)
	: Component(owner)
	, mUseGravity(false)
	, mGravityScale(2)
	, mMass(1.0f)
{
	mUseGravity = true;
}

void Rigidbody::FixedUpdate(float deltaTime)
{
    Vector3 gravityForce;
    //重力フラグが有効なら
    if (mUseGravity)
    {
        // 重力を力として加える
        gravityForce = Vector3::UnitY * (-9.8f) * mMass * mGravityScale;
    }
    mForces += gravityForce;

    // 運動方程式: F = ma → a = F / m
    Vector3 acceleration = mForces / mMass;

    // 速度更新
    mVelocity += acceleration * deltaTime;

    // 位置更新
    Vector3 position = mOwner->GetLocalPosition();
    position += mVelocity * deltaTime;
    mOwner->SetLocalPosition(position);

    // 力のリセット
    //（次フレームでまたAddForceするため）
    mForces = Vector3::Zero;
}

void Rigidbody::AddForce(Vector3 force)
{
    mForces += force;
}
