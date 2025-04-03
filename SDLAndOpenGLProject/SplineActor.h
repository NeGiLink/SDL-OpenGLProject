#pragma once
#include "Actor.h"

class SplineActor : public ActorObject
{
public:
	SplineActor(class BaseScene* game);

	void ActorInput(const bool* keys) override;

	void RestartSpline();
private:
	class SplineCamera* mCameraComp;
};

