#include "BasicInputAction.h"

BasicInputAction::BasicInputAction(ActorObject* owner, int updateOrder)
	:Component(owner, updateOrder)
	, mAngularSpeed(0.0f)
	, mForwardSpeed(0.0f)
{
	mGravity = false;
	mJumping = false;
}

void BasicInputAction::Update(float deltaTime)
{
	//���_��]
	if (!Math::NearZero(mAngularSpeed))
	{
		Quaternion rot = mOwner->GetLocalRotation();
		float angle = mAngularSpeed * deltaTime;
		// Create quaternion for incremental rotation
		// (Rotate about up axis)
		Quaternion inc(Vector3::UnitY, angle);
		// Concatenate old and new quaternion
		rot = Quaternion::Concatenate(rot, inc);
		mOwner->SetRotation(rot);
	}
	//X�AZ�ړ�����
	if (!Math::NearZero(mForwardSpeed) || !Math::NearZero(mStrafeSpeed))
	{
		Vector3 pos = mOwner->GetLocalPosition();
		pos += mOwner->GetForward() * mForwardSpeed * deltaTime;
		pos += mOwner->GetRight() * mStrafeSpeed * deltaTime;
		mOwner->SetPosition(pos);
	}

	if (mGravity)
	{
		if (!Math::NearZero(mJumpPower) && !mJumping)
		{
			Vector3 pos = mOwner->GetLocalPosition();
			pos += mOwner->GetUp() * mJumpPower * deltaTime;
			mOwner->SetPosition(pos);
		}
		else
		{
			Vector3 pos = mOwner->GetLocalPosition();
			pos -= mOwner->GetUp() * 4.905f * deltaTime;
			mOwner->SetPosition(pos);
		}
	}
	else
	{
		if (!Math::NearZero(mJumpPower))
		{
			Vector3 pos = mOwner->GetLocalPosition();
			pos += mOwner->GetUp() * mJumpPower * deltaTime;
			mOwner->SetPosition(pos);
		}
	}
}

void BasicInputAction::MoveInputUpdate(const InputState& keys)
{
	float forwardSpeed = 0.0f;
	float strafeSpeed = 0.0f;
	float upSpeed = 0.0f;
	// wasd movement
	if (keys.Keyboard.GetKey(SDL_SCANCODE_W))
	{
		forwardSpeed += 4.0f;
	}
	if (keys.Keyboard.GetKey(SDL_SCANCODE_S))
	{
		forwardSpeed -= 4.0f;
	}
	if (keys.Keyboard.GetKey(SDL_SCANCODE_A))
	{
		strafeSpeed -= 4.0f;
	}
	if (keys.Keyboard.GetKey(SDL_SCANCODE_D))
	{
		strafeSpeed += 4.0f;
	}
	if (mGravity)
	{
		if (keys.Keyboard.GetKey(SDL_SCANCODE_SPACE))
		{
			upSpeed += 250.0f;
		}
	}
	else
	{
		if (keys.Keyboard.GetKey(SDL_SCANCODE_SPACE))
		{
			if (keys.Keyboard.GetKey(SDL_SCANCODE_LSHIFT))
			{
				upSpeed -= 4.0f;
			}
			else
			{
				upSpeed += 4.0f;
			}
		}
	}

	mForwardSpeed = forwardSpeed;
	mStrafeSpeed = strafeSpeed;
	mJumpPower = upSpeed;
}

float BasicInputAction::CameraInputUpdate()
{
	//SDL�Ń}�E�X�̈ړ����l���擾
	float x, y;
	SDL_GetRelativeMouseState(&x, &y);
	//�}�E�X�ł̍ő�ړ����l��ݒ�
	const int maxMouseSpeed = 500;
	// �ő呬�x�ł̉�]/�b
	const float maxAngularSpeed = Math::Pi * 8;
	float angularSpeed = 0.0f;
	if (x != 0)
	{
		// [-1.0, 1.0]�ɕϊ�����
		angularSpeed = static_cast<float>(x) / maxMouseSpeed;
		// ��]/�b�Ŋ|����
		angularSpeed *= maxAngularSpeed;
	}
	mAngularSpeed = angularSpeed;

	// �������v�Z����
	const float maxPitchSpeed = Math::Pi * 8;
	float pitchSpeed = 0.0f;
	if (y != 0)
	{
		// [-1.0, 1.0]�ɕϊ�����
		pitchSpeed = static_cast<float>(y) / maxMouseSpeed;
		pitchSpeed *= maxPitchSpeed;
	}
	return pitchSpeed;
}
