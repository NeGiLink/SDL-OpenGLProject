#pragma once
#include "Actor.h"

class SphereActor : public ActorObject
{
public:
	SphereActor(class BaseScene* game);

	void UpdateActor(float deltaTime) override;

	class SphereCollider* GetSphere() { return mSphere; }

	void OnCollisionEnter(class ActorObject* target) override;
private:
	class SphereCollider* mSphere;
};

