#include "CapsuleCollider.h"

CapsuleCollider::CapsuleCollider(ActorObject* owner, int updateOrder)
	: Collider(owner,updateOrder)
	, mObjectCapsule(Vector3::Zero,Vector3::Zero,0.0f)
	, mWorldCapsule(Vector3::Zero, Vector3::Zero, 0.0f)
	, mShouldRotate(true)
{
}

CapsuleCollider::~CapsuleCollider()
{
}

void CapsuleCollider::OnUpdateWorldTransform()
{
    mWorldCapsule = mObjectCapsule;

    // �X�P�[���E��]�E�ʒu���擾
    Vector3 scale = mOwner->GetScale();
    Quaternion rot = mOwner->GetRotation();
    Vector3 pos = mOwner->GetPosition();

    // ��]�{�X�P�[�� �� �n�_�E�I�_�����[���h�ϊ�
    Vector3 localStart = mWorldCapsule.mSegment.mStart;
    Vector3 localEnd = mWorldCapsule.mSegment.mEnd;

    Vector3 rotatedStart = rot.Rotate(localStart);
    Vector3 rotatedEnd = rot.Rotate(localEnd);

    mWorldCapsule.mSegment.mStart = rotatedStart + pos;
    mWorldCapsule.mSegment.mEnd = rotatedEnd + pos;

    // ���a�X�P�[���i�����X�P�[���z�� or �ő厲�X�P�[���g�p�j
    float uniformScale = std::max({ scale.x, scale.y, scale.z });
    mWorldCapsule.mRadius = mWorldCapsule.mRadius * uniformScale;

}

OBB CapsuleCollider::GetWorldOBB() const
{
    return mWorldOBB;
}

AABB CapsuleCollider::GetWorldAABBFromOBB() const
{
    const Vector3& p0 = mWorldCapsule.mSegment.mStart;
    const Vector3& p1 = mWorldCapsule.mSegment.mEnd;
    float r = mWorldCapsule.mRadius;

    Vector3 min = Vector3::Min(p0, p1);
    Vector3 max = Vector3::Max(p0, p1);

    Vector3 rVec(r, r, r);
    return AABB(min - rVec, max + rVec);
}
