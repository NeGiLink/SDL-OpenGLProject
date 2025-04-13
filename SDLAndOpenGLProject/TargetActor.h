#pragma once
#include "Actor.h"

class TargetActor : public ActorObject
{
public:
	TargetActor(class BaseScene* game);
private:
	std::vector<class BoxCollider*>	mBoxs;

	class MeshRenderer*					mMeshComp;
};