#pragma once
#include "Component.h"

//レーダーのUIに表示するためのコンポーネント
class TargetComponent : public Component
{
public:
	TargetComponent(class ActorObject* owner);
	~TargetComponent();
};

