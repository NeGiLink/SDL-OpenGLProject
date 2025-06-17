#include "FPSCameraActor.h"

FPSCameraActor::FPSCameraActor()
	:ActorObject()
{
	mFPSCamera = new FPSCamera(this);
}

void FPSCameraActor::ActorInput(const InputState& keys)
{
	mFPSCamera->CameraInputUpdate();
}
