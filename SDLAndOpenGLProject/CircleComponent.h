#pragma once
#include "Component.h"
#include "Math.h"

//‹…‚ÌCollision
class CircleComponent : public Component
{
public:
	CircleComponent(class ActorObject* owner);

	void SetRadius(float radius) { mRadius = radius; }
	Vector3 GetRadius() const;

	const Vector3& GetCenter() const;
private:
	float mRadius;
};

bool Intersect(const CircleComponent& a, const CircleComponent& b);