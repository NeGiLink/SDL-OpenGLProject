#pragma once
#include "Actor.h"
#include "MeshRenderer.h"
#include "Skeleton.h"
//剣オブジェクトのクラス
class Sword : public ActorObject
{
public:
	Sword(class BaseScene* game);
	void ActorInput(const struct InputState& keys) override;
	void UpdateRightHand(Skeleton::Bone* hand);
private:

	Vector3				mPos;

	float				mAngleY;
	float				mAngleX;
	float				mAngleZ;
};

