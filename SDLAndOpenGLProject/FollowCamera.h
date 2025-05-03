#pragma once
#include "BaseCamera.h"
#include "Actor.h"

//三人称視点カメラのクラス
class FollowCamera : public BaseCamera
{
public:
	FollowCamera(class ActorObject* owner);

	void Update(float deltaTime) override;

	void SnapToIdeal();

	void SetHorzDist(float dist) { mHorzDist = dist; }
	void SetVertDist(float dist) { mVertDist = dist; }
	void SetTargetDist(float dist) { mTargetDist = dist; }
	void SetSpringConstant(float spring) { mSpringConstant = spring; }
private:
	Vector3 ComputeCameraPos() const;

	// カメラの位置
	Vector3		mActualPos;
	// 実際のカメラの速度
	Vector3		mVelocity;
	// 水平追従距離
	float		mHorzDist;
	// 垂直フォロー距離
	float		mVertDist;
	// 目標との距離
	float		mTargetDist;
	// ばね定数（高いほど硬い）
	float		mSpringConstant;
};

