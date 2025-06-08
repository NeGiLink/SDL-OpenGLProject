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
    if (mUseGravity && !mIsGrounded)
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

    // ��ԃ��Z�b�g�i�����ResolveCollision�ōăZ�b�g�����j
    mIsGrounded = false;
}

void Rigidbody::ResolveCollision(const Vector3& push)
{
    Vector3 pushNormal = push.Normalized();
    float normalSpeed = Vector3::Dot(mVelocity, pushNormal);

    if (normalSpeed < 0.0f)
    {
        // �ڒn��Ԃ����o�i�@����������ɋ߂������j
        if (pushNormal.y > 0.7f)
        {
            mIsGrounded = true;
        }

        // �� �o�E���h�i�����W���j
        Vector3 bounce = (-1.0f * pushNormal) * normalSpeed * mBounciness;

        // �� ���C�F�ڐG�ʂƕ��s�ȑ��x
        Vector3 tangent = mVelocity - (pushNormal * normalSpeed);
        tangent *= (1.0f - mFriction);

        // �� �ŏI�I�ȑ��x = �����{���C
        mVelocity = bounce + tangent;

        // �����Ȕ����𖳌��Ɂi�Î~����j
        if (std::abs(Vector3::Dot(mVelocity, pushNormal)) < 0.01f)
        {
            //mVelocity -= pushNormal * Vector3::Dot(mVelocity, pushNormal);
            mVelocity = Vector3::Zero;
        }
    }
}

void Rigidbody::AddForce(Vector3 force)
{
    mForces += force;
}
