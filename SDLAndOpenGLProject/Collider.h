#pragma once
#include "Component.h"

class Collider : public Component
{
public:
	Collider(class ActorObject* owner, int updateOrder = 100);
	~Collider();

	enum ColliderType
	{
		Box,
		Sphere,
		Capsule
	};
	virtual ColliderType GetType() = 0;
protected:
	ColliderType type;
};

