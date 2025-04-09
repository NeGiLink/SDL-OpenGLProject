#pragma once
#include "Actor.h"
#include "MeshRenderer.h"
#include "Skeleton.h"

class Sword : public ActorObject
{
public:
	Sword(class BaseScene* game);
	void ActorInput(const bool* keys) override;
	void UpdateRightHand(Skeleton::Bone* hand);
private:
	Skeleton::Bone* mRightHand;

	Vector3 mPos;

	float mAngleY;
	float mAngleX;
	float mAngleZ;

	Vector3 mS;
};

