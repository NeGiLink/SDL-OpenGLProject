#include "SphereCollider.h"

SphereCollider::SphereCollider(ActorObject* owner, int updateOrder)
	:Collider(owner, updateOrder)
	, mObjectSphere(Vector3::Zero, 0)
	, mWorldSphere(Vector3::Zero, 0)
	, mShouldRotate(true)
{
}

SphereCollider::~SphereCollider()
{
}

void SphereCollider::OnUpdateWorldTransform()
{
	mWorldSphere = mObjectSphere;

	Vector3 scale = mOwner->GetLocalScale();
	float maxScale = std::max({ scale.x, scale.y, scale.z });
	
	mWorldSphere.mRadius = mObjectSphere.mRadius * maxScale;

	mWorldSphere.mCenter = mObjectSphere.mCenter * maxScale + mOwner->GetLocalPosition();
}
