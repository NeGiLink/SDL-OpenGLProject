#pragma once
#include "Component.h"
#include "Math.h"

//ƒJƒƒ‰‚ÌŠî’êƒNƒ‰ƒX
class BaseCamera : public Component
{
public:
	BaseCamera(class ActorObject* owner, int updateOrder = 200);

	Vector3 GetCameraForward() { return mCameraForward; }
	Vector3 GetCameraRight() { return mCameraRight; }
	Vector3 GetCameraUp() { return mCameraUp; }
	Matrix4 GetCameraYawRot() { return mCameraYawRot; }
protected:
	void SetViewMatrix(const Matrix4& view);

	Vector3 mCameraForward;
	Vector3 mCameraRight;
	Vector3 mCameraUp;

	Matrix4 mCameraYawRot;
};