#pragma once
#include "Actor.h"
#include "MeshRenderer.h"
#include "FreeCamera.h"

class FreeCameraActor : public ActorObject
{
private:
	class FreeCamera* mCameraComp;
public:
							FreeCameraActor();

							class FreeCamera* GetCamera() { return mCameraComp; }
};

