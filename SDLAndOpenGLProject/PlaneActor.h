#pragma once
#include "Actor.h"

class PlaneActor : public ActorObject
{
public:
	PlaneActor(class BaseScene* game);
	~PlaneActor();
	std::vector<class BoxCollider*> GetBoxs() { return mBoxs; }
private:
	std::vector<class BoxCollider*> mBoxs;

	class MeshRenderer* mMeshComp;
};