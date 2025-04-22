#pragma once
#include "Actor.h"

class CapsuleActor : public ActorObject
{
public:
	CapsuleActor();

	void UpdateActor(float deltaTime) override;

	class CapsuleCollider* GetCapsule() { return mCapsule; }

	void OnCollisionEnter(class ActorObject* target) override;
private:
	class CapsuleCollider* mCapsule;
};