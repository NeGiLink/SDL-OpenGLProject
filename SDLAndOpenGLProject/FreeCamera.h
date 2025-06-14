#pragma once
#include "BaseCamera.h"
#include "Actor.h"

//指定した方向を映すカメラ
class FreeCamera : public BaseCamera
{
private:
	bool	isUpdatePosition;

	// カメラの上方向ベクトル。
	Vector3		mUp;
public:
			FreeCamera(class ActorObject* owner);

	void    Initiailze();

	void	Update(float deltaTime) override;

	void    SetCameraPosition(const Vector3& eye, const Vector3& target);
};

