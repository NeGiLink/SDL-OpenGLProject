#include "Rigidbody.h"

Rigidbody::Rigidbody(ActorObject* owner, int updateOrder)
	: Component(owner)
	, mUseGravity(false)
	, mGravityScale(2)
	, mMass(1.0f)
    , mFriction(0.3f)
    , mBounciness(0.1f)
    , mSolverIterationCount(4)
{
	mUseGravity = true;
}

void Rigidbody::FixedUpdate(float deltaTime)
{
    Vector3 gravityForce;
    //�d�̓t���O���L���Ȃ�
    if (mUseGravity)
    {
        // �d�͂�͂Ƃ��ĉ�����
        gravityForce = Vector3::UnitY * (-9.8f) * mMass * mGravityScale;
    }
    mForces += gravityForce;

    // �^��������: F = ma �� a = F / m
    Vector3 acceleration = mForces / mMass;

    // ���x�X�V
    mVelocity += acceleration * deltaTime;

    // �ʒu�X�V
    Vector3 position = mOwner->GetLocalPosition();
    position += mVelocity * deltaTime;
    mOwner->SetLocalPosition(position);

    // �͂̃��Z�b�g
    //�i���t���[���ł܂�AddForce���邽�߁j
    mForces = Vector3::Zero;
}

Vector3 Rigidbody::ResolveCollision(const Vector3& velocity, PhysWorld::Axis normalAxis) const
{
    Vector3 newVelocity = velocity;

    switch (normalAxis)
    {
    case PhysWorld::Axis::X:
        newVelocity.x *= -mBounciness;
        if (std::abs(newVelocity.x) < 0.01f) newVelocity.x = 0.0f;
        newVelocity.x *= (1.0f - mFriction);
        break;
    case PhysWorld::Axis::Y:
        newVelocity.y *= -mBounciness;
        if (std::abs(newVelocity.y) < 0.01f) newVelocity.y = 0.0f;
        newVelocity.y *= (1.0f - mFriction);
        break;
    case PhysWorld::Axis::Z:
        newVelocity.z *= -mBounciness;
        if (std::abs(newVelocity.z) < 0.01f) newVelocity.z = 0.0f;
        newVelocity.z *= (1.0f - mFriction);
        break;
    }

    return newVelocity;
}

void Rigidbody::AddForce(Vector3 force)
{
    mForces += force;
}
