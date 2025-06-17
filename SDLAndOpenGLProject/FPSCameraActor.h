#pragma once
#include "Actor.h"
#include "MeshRenderer.h"
#include "FPSCamera.h"

class FPSCameraActor : public ActorObject
{
private:
	FPSCamera* mFPSCamera;
public:
							FPSCameraActor();

	void					ActorInput(const struct InputState& keys) override;

	FPSCamera* GetFPSCamera() { return mFPSCamera; }
};

