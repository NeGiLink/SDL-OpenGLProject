#include "FreeCameraActor.h"

FreeCameraActor::FreeCameraActor()
	:ActorObject()
{
	SetLocalPosition(Vector3(0.0f, 0.0f, 0.0f));

	mCameraComp = new FreeCamera(this);
}
