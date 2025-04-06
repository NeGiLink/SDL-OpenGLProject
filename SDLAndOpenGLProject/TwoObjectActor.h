#pragma once
#include "Actor.h"

class TwoObjectActor : public ActorObject
{
public:
	TwoObjectActor(class BaseScene* game);
	void UpdateActor(float deltaTime) override;
private:
};

