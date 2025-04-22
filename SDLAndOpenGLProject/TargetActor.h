#pragma once
#include "Actor.h"

class TargetActor : public ActorObject
{
public:
	TargetActor();
private:
	std::vector<class BoxCollider*>	mBoxs;

	class MeshRenderer*					mMeshComp;
};