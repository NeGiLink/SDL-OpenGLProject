#include "FollowCamera.h"
#include "Actor.h"

FollowCamera::FollowCamera(ActorObject* owner)
	:CameraComponent(owner)
	, mHorzDist(350.0f)
	, mVertDist(150.0f)
	, mTargetDist(100.0f)
	, mSpringConstant(64.0f)
{
}

void FollowCamera::Update(float deltaTime)
{
	CameraComponent::Update(deltaTime);
	// ばね定数から減衰を計算する
	float dampening = 2.0f * Math::Sqrt(mSpringConstant);
	// 理想的な位置を計算する
	Vector3 idealPos = ComputeCameraPos();
	// 実際と理想の違いを計算する
	Vector3 diff = mActualPos - idealPos;
	// ばねの加速度を計算する
	Vector3 acel = -mSpringConstant * diff -
		dampening * mVelocity;
	// 更新速度
	mVelocity += acel * deltaTime;
	// 実際のカメラ位置を更新する
	mActualPos += mVelocity * deltaTime;
	// ターゲットは所有者アクターの前方にあるターゲット距離
	Vector3 target = mOwner->GetPosition() +
		mOwner->GetForward() * mTargetDist;
	// 理想ではなく、ここに実際の位置を使用してください。
	Matrix4 view = Matrix4::CreateLookAt(mActualPos, target,
		Vector3::UnitZ);
	SetViewMatrix(view);
}

void FollowCamera::SnapToIdeal()
{
	// 実際の位置を理想に設定する
	mActualPos = ComputeCameraPos();
	// ゼロ速度
	mVelocity = Vector3::Zero;
	// ターゲットを計算して表示
	Vector3 target = mOwner->GetPosition() +
		mOwner->GetForward() * mTargetDist;
	// 理想ではなく、ここに実際の位置を使用してください。
	Matrix4 view = Matrix4::CreateLookAt(mActualPos, target,
		Vector3::UnitZ);
	SetViewMatrix(view);
}

Vector3 FollowCamera::ComputeCameraPos() const
{
	// Actorの後ろと上にカメラの位置を設定する
	Vector3 cameraPos = mOwner->GetPosition();
	cameraPos -= mOwner->GetForward() * mHorzDist;
	cameraPos += Vector3::UnitZ * mVertDist;
	return cameraPos;
}