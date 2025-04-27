#pragma once
#include "Actor.h"
#include "MeshRenderer.h"
#include "BoxCollider.h"
#include "Mesh.h"
#include "TargetComponent.h"

class TargetActor : public ActorObject
{
public:
	TargetActor();
private:
	std::vector<class BoxCollider*>	mBoxs;

	class MeshRenderer*					mMeshComp;
};