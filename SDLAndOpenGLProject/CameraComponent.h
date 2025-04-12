#pragma once
#include "Component.h"
#include "Math.h"

//�J�����̊��N���X
class CameraComponent : public Component
{
public:
	CameraComponent(class ActorObject* owner, int updateOrder = 200);
protected:
	void SetViewMatrix(const Matrix4& view);
};