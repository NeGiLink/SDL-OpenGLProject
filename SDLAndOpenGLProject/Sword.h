#pragma once
#include "Actor.h"
#include "MeshRenderer.h"
#include "Skeleton.h"
//���I�u�W�F�N�g�̃N���X
class Sword : public ActorObject
{
public:
	Sword(class BaseScene* game);
	void ActorInput(const bool* keys) override;
	void UpdateRightHand(Skeleton::Bone* hand);
private:
	Skeleton::Bone*		mRightHand;

	Vector3				mPos;

	float				mAngleY;
	float				mAngleX;
	float				mAngleZ;
};

