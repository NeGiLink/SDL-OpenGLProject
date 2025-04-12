#pragma once
#include "CameraComponent.h"

//軌道カメラのクラス
class OrbitCamera : public CameraComponent
{
public:
	OrbitCamera(class ActorObject* owner);

	void Update(float deltaTime) override;

	float GetPitchSpeed() const { return mPitchSpeed; }
	float GetYawSpeed() const { return mYawSpeed; }

	void SetPitchSpeed(float speed) { mPitchSpeed = speed; }
	void SetYawSpeed(float speed) { mYawSpeed = speed; }
private:
	// ターゲットのオフセット。
	Vector3 mOffset;
	// カメラの上方向ベクトル。
	Vector3 mUp;
	// ピッチの回転/秒速度。
	float mPitchSpeed;
	// ヨーの回転/秒速度。
	float mYawSpeed;
};

