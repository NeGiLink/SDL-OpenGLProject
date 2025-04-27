#pragma once
#include "CameraComponent.h"
#include "Actor.h"

//一人称視点カメラのクラス
class FPSCamera : public CameraComponent
{
public:
	FPSCamera(class ActorObject* owner);

	void Update(float deltaTime) override;

	float GetPitch() const { return mPitch; }
	float GetPitchSpeed() const { return mPitchSpeed; }
	float GetMaxPitch() const { return mMaxPitch; }

	void SetPitchSpeed(float speed) { mPitchSpeed = speed; }
	void SetMaxPitch(float pitch) { mMaxPitch = pitch; }
private:
	// ピッチの回転/秒速度。
	float mPitchSpeed;
	// 前方からの最大ピッチ偏差。
	float mMaxPitch;
	// 現在のピッチ。
	float mPitch;
};

