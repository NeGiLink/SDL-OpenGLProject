#include "BasicInputAction.h"

BasicInputAction::BasicInputAction(ActorObject* owner, int updateOrder)
	:Component(owner, updateOrder)
	, mForwardSpeed(0.0f)
{
	mGravity = true;
	mJumping = false;
}

void BasicInputAction::Update(float deltaTime)
{

	//XAZˆÚ“®ˆ—
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
		/*
		else
		{
			Vector3 pos = mOwner->GetLocalPosition();
			pos -= mOwner->GetUp() * 4.905f * deltaTime;
			mOwner->SetPosition(pos);
		}
		*/
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