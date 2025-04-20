#pragma once
#include "Actor.h"

class CubeActor : public ActorObject
{
public:
	CubeActor(class BaseScene* game);

	std::vector<class BoxCollider*> GetBoxs() { return mBoxs; }

	void UpdateActor(float deltaTime) override;

	void ActorInput(const struct InputState& keys) override;

	void OnCollisionEnter(class ActorObject* target) override;
private:
	std::vector<class BoxCollider*> mBoxs;
};

