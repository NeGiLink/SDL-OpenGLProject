#pragma once
#include "Actor.h"
#include "DirectionalLightComponent.h"

class DirectionalLightActor : public ActorObject
{
private:
	DirectionalLightComponent* mDirectionalLightComp;
public:
	DirectionalLightActor();
	~DirectionalLightActor();

	void ActorInput(const struct InputState& keyState)override;
};
