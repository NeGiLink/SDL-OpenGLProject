#pragma once
#include "Actor.h"
#include "MeshRenderer.h"
#include "Skeleton.h"

class Sword : public ActorObject
{
public:
	Sword(class BaseScene* game);
	void UpdateActor(float deltaTime) override;
	void UpdateRightHand(Skeleton::Bone* hand);
private:
	Skeleton::Bone* mRightHand;
};

