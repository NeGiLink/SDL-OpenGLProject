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

void Rigidbody::AddForce(Vector3 force)
{
    mForces += force;
}
