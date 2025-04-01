#pragma once
#include "Actor.h"

class OrbitActor : public ActorObject
{
public:
	OrbitActor(class WinMain* game);

	void ActorInput(const bool* keys) override;

	void SetVisible(bool visible);
private:
	class OrbitCamera* mCameraComp;
	class MeshComponent* mMeshComp;
};

