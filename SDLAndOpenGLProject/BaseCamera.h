#pragma once
#include "Component.h"
#include "Math.h"

//�J�����̊��N���X
class BaseCamera : public Component
{
public:
	BaseCamera(class ActorObject* owner, int updateOrder = 200);
protected:
	void SetViewMatrix(const Matrix4& view);
};