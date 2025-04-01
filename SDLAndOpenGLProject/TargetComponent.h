#pragma once
#include "Component.h"

class TargetComponent : public Component
{
public:
	TargetComponent(class ActorObject* owner);
	~TargetComponent();
};

