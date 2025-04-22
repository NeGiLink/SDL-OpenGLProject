#include "FPSCamera.h"
#include "Actor.h"

FPSCamera::FPSCamera(ActorObject* owner)
	:CameraComponent(owner)
	, mPitchSpeed(0.0f)
	, mMaxPitch(Math::Pi / 3.0f)
	, mPitch(0.0f)
{
}

void FPSCamera::Update(float deltaTime)
{
	// 親更新を呼び出す。（今は何もしない）
	CameraComponent::Update(deltaTime);
	// カメラの位置はオーナーの位置です。
	Vector3 cameraPos = mOwner->GetLocalPosition();

	// ピッチ速度に基づいてピッチを更新する。
	mPitch += mPitchSpeed * deltaTime;
	// クランプピッチを[-max, +max]に制限する。
	mPitch = Math::Clamp(mPitch, -mMaxPitch, mMaxPitch);
	// オーナーの右ベクトルを軸とするピッチ回転を表す四元数を作成します。
	Quaternion q(mOwner->GetRight(), mPitch);

	// 所有者をピッチクォータニオンで前方に回転させる。
	Vector3 viewForward = Vector3::Transform(
		mOwner->GetForward(), q);
	// 視線の前方100ユニットのターゲット位置。
	Vector3 target = cameraPos + viewForward * 100.0f;
	// ピッチクォータニオンを回転。
	Vector3 up = Vector3::Transform(Vector3::UnitY, q);

	// マトリックスを作成し、ビューとして設定します。
	Matrix4 view = Matrix4::CreateLookAt(cameraPos, target, up);
	SetViewMatrix(view);
}