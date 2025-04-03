#pragma once
#include "Actor.h"

class OrbitActor : public ActorObject
{
public:
	OrbitActor(class BaseScene* game);

	void ActorInput(const bool* keys) override;

	void SetVisible(bool visible);
private:
	class OrbitCamera* mCameraComp;
	class MeshRenderer* mMeshComp;
};

