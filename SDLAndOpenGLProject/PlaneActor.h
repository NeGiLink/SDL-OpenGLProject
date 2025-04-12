#pragma once
#include "Actor.h"

class PlaneActor : public ActorObject
{
public:
	PlaneActor(class BaseScene* game);
	~PlaneActor();
	std::vector<class BoxComponent*> GetBoxs() { return mBoxs; }
private:
	std::vector<class BoxComponent*> mBoxs;

	class MeshRenderer* mMeshComp;
};