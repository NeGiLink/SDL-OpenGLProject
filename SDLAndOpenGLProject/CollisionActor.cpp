#include "CollisionActor.h"


ColliderActor::ColliderActor()
	: Transform()
	, mRigidbody(nullptr)
	, mCollider(nullptr)
{
}

ColliderActor::~ColliderActor()
{
}
