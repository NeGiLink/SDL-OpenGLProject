#include "Collider.h"


Collider::Collider(ActorObject* owner, int updateOrder)
	:Component(owner,updateOrder)
	, mWorldBox(Vector3::Zero, Vector3::Zero)
	, collider(true)
	, staticObject(true)
{
	mOwner->GetGame()->GetPhysWorld()->AddCollider(this);
}

Collider::~Collider()
{
	mOwner->GetGame()->GetPhysWorld()->RemoveCollider(this);
}
