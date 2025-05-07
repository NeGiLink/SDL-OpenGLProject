#pragma once
#include "Actor.h"
#include "FollowCamera.h"

class TPSCamera : public ActorObject
{
public:
	TPSCamera();
	class FollowCamera* GetFollowCamera() { return mFollowCamera; }
private:
	class FollowCamera* mFollowCamera;
};

