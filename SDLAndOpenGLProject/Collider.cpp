#include "Collider.h"
#include "Actor.h"
#include "BaseScene.h"
#include "PhysWorld.h"

Collider::Collider(ActorObject* owner, int updateOrder)
	:Component(owner,updateOrder)
{
	//mOwner->GetGame()->GetPhysWorld()->AddBox(this);
}

Collider::~Collider()
{
	//mOwner->GetGame()->GetPhysWorld()->RemoveBox(this);
}
