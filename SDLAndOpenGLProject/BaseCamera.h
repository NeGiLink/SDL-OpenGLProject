#pragma once
#include "Component.h"
#include "Math.h"

//ƒJƒƒ‰‚ÌŠî’êƒNƒ‰ƒX
class BaseCamera : public Component
{
public:
	BaseCamera(class ActorObject* owner, int updateOrder = 200);
protected:
	void SetViewMatrix(const Matrix4& view);
};