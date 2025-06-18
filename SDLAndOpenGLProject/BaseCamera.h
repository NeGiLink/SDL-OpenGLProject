#pragma once
#include "Component.h"
#include "Math.h"

/*
* ===�G���W����������/Engine internal processing===
*/

//�J�����̊��N���X
class BaseCamera : public Component
{
protected:
	void SetViewMatrix(const Matrix4& view);

	Vector3 mCameraForward;
	Vector3 mCameraRight;
	Vector3 mCameraUp;

	Matrix4 mCameraYawRot;
public:
	BaseCamera(class ActorObject* owner, int updateOrder = 200);

	Vector3 GetCameraForward() { return mCameraForward; }
	Vector3 GetCameraRight() { return mCameraRight; }
	Vector3 GetCameraUp() { return mCameraUp; }
	Matrix4 GetCameraYawRot() { return mCameraYawRot; }
};