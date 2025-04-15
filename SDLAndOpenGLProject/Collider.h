#pragma once
#include "Component.h"
#include "Collision.h"

class Collider : public Component
{
public:
	Collider(class ActorObject* owner, int updateOrder = 100);
	~Collider();

	enum ColliderType
	{
		BoxType,
		SphereType,
		CapsuleType
	};
	virtual ColliderType GetType() = 0;
	virtual const AABB& GetWorldBox() const = 0;
	virtual const Sphere& GetWorldSphere() const = 0;
	virtual const Capsule& GetWorldCapsule() const = 0;
protected:
	AABB mWorldBox;
};

