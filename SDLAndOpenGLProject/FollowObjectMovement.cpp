#include "FollowObjectMovement.h"

FollowObjectMovement::FollowObjectMovement(ActorObject* owner, int updateOrder)
	:Component(owner, updateOrder)
	, mMaxSpeed(8.0f)
{
}

void FollowObjectMovement::FixedUpdate(float deltaTime)
{
	float rotationSpeed = 600.0f * deltaTime;
	Quaternion targetRotation;
	if (!Math::NearZero(mVelocity.x)|| !Math::NearZero(mVelocity.y)|| !Math::NearZero(mVelocity.z))
	{
		targetRotation = Quaternion::LookRotation(mVelocity, Vector3::UnitY);
		Quaternion currnetRotation = Quaternion::RotateTowards(mOwner->GetLocalRotation(), targetRotation, rotationSpeed);
		mOwner->SetLocalRotation(currnetRotation);
	}


	//New X、Z移動処理
	if (!Math::NearZero(mVelocity.x) || !Math::NearZero(mVelocity.z))
	{
		Vector3 pos = mOwner->GetLocalPosition();
		pos += mOwner->GetForward() * (mMaxSpeed * mVelocity.z) * deltaTime;
		pos += mOwner->GetRight() * (mMaxSpeed * mVelocity.x) * deltaTime;
		mOwner->SetLocalPosition(pos);
	}
}

void FollowObjectMovement::Update(float deltaTime)
{
	Vector3 inputDir = mInputDir;

	// カメラの回転行列を取得（yawだけ）
	// Y軸回転のみ
	Matrix4 cameraYawRot = mGame->GetCamera()->GetCameraYawRot();
	Vector3 moveDir = Vector3::Transform(inputDir, cameraYawRot);

	mVelocity = moveDir;
}

void FollowObjectMovement::MoveInputUpdate(const InputState& keys)
{
	mInputDir = Vector3();
	// wasd movement
	if (keys.Keyboard.GetKey(SDL_SCANCODE_W))
	{
		mInputDir.z = 1.0f;
	}
	if (keys.Keyboard.GetKey(SDL_SCANCODE_S))
	{
		mInputDir.z = -1.0f;
	}
	if (keys.Keyboard.GetKey(SDL_SCANCODE_A))
	{
		mInputDir.x = -1.0f;
	}
	if (keys.Keyboard.GetKey(SDL_SCANCODE_D))
	{
		mInputDir.x = 1.0f;
	}

	if (mGravity)
	{
		if (keys.Keyboard.GetKeyDown(SDL_SCANCODE_SPACE) && !mJumping)
		{
			if (mOwner->GetRigidbody())
			{
				mOwner->GetRigidbody()->AddForce(Vector3::UnitY * 2000.0f);
			}
		}
	}
}
