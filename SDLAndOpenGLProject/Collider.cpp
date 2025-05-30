#include "Collider.h"


Collider::Collider(ActorObject* owner, int updateOrder)
	:Component(owner,updateOrder)
	, mWorldBox(Vector3::Zero, Vector3::Zero)
	, mCollider(true)
	, mStaticObject(true)
	, mContactOffset(0.001f)
{
	mOwner->GetGame()->GetPhysWorld()->AddCollider(this);
}

Collider::~Collider()
{
	mOwner->GetGame()->GetPhysWorld()->RemoveCollider(this);
}
