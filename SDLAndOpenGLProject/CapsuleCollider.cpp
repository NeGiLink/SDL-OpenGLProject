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

    // スケール・回転・位置を取得
    Vector3 scale = mOwner->GetLocalScale();
    Quaternion rot = mOwner->GetLocalRotation();
    Vector3 pos = mOwner->GetLocalPosition();

    // 回転＋スケール → 始点・終点をワールド変換
    Vector3 localStart = mWorldCapsule.mSegment.mStart;
    Vector3 localEnd = mWorldCapsule.mSegment.mEnd;

    Vector3 rotatedStart = rot.Rotate(localStart);
    Vector3 rotatedEnd = rot.Rotate(localEnd);

    mWorldCapsule.mSegment.mStart = rotatedStart + pos;
    mWorldCapsule.mSegment.mEnd = rotatedEnd + pos;

    // 半径スケール（等方スケール想定 or 最大軸スケール使用）
    float uniformScale = std::max({ scale.x, scale.y, scale.z });
    mWorldCapsule.mRadius = mWorldCapsule.mRadius * uniformScale;

}
