#include "Collider.h"
#include "Actor.h"
#include "BaseScene.h"
#include "PhysWorld.h"

Collider::Collider(ActorObject* owner, int updateOrder)
	:Component(owner,updateOrder)
	, mWorldBox(Vector3::Zero, Vector3::Zero)
{
	mOwner->GetGame()->GetPhysWorld()->AddCollider(this);
}

Collider::~Collider()
{
	mOwner->GetGame()->GetPhysWorld()->RemoveCollider(this);
}
