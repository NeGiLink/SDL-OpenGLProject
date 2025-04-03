#pragma once
#include "Actor.h"

class PlaneActor : public ActorObject
{
public:
	PlaneActor(class BaseScene* game);
	~PlaneActor();
	//class BoxComponent* GetBox() { return mBox; }
	std::vector<class BoxComponent*> GetBoxs() { return mBoxs; }
private:
	//class BoxComponent* mBox;
	std::vector<class BoxComponent*> mBoxs;
};