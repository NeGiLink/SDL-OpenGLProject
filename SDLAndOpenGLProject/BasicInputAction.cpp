#include "BasicInputAction.h"

BasicInputAction::BasicInputAction(ActorObject* owner, int updateOrder)
	:Component(owner, updateOrder)
	, mForwardSpeed(0.0f)
{
	mGravity = true;
	mJumping = false;
}

void BasicInputAction::FixedUpdate(float deltaTime)
{
	//XAZˆÚ“®ˆ—
	if (!Math::NearZero(mForwardSpeed) || !Math::NearZero(mStrafeSpeed))
	{
		Vector3 pos = mOwner->GetLocalPosition();
		pos += mOwner->GetForward() * mForwardSpeed * deltaTime;
		pos += mOwner->GetRight() * mStrafeSpeed * deltaTime;
		mOwner->SetLocalPosition(pos);
	}
}

void BasicInputAction::Update(float deltaTime)
{

}

void BasicInputAction::MoveInputUpdate(const InputState& keys)
{
	float forwardSpeed = 0.0f;
	float strafeSpeed = 0.0f;
	float upSpeed = 0.0f;
	// wasd movement
	if (keys.Keyboard.GetKey(SDL_SCANCODE_W))
	{
		forwardSpeed += 8.0f;
	}
	if (keys.Keyboard.GetKey(SDL_SCANCODE_S))
	{
		forwardSpeed -= 8.0f;
	}
	if (keys.Keyboard.GetKey(SDL_SCANCODE_A))
	{
		strafeSpeed -= 8.0f;
	}
	if (keys.Keyboard.GetKey(SDL_SCANCODE_D))
	{
		strafeSpeed += 8.0f;
	}
	if (mGravity)
	{
		if (keys.Keyboard.GetKeyDown(SDL_SCANCODE_SPACE) && !mJumping)
		{
			//upSpeed += 250.0f;
			if (mOwner->GetRigidbody())
			{
				mOwner->GetRigidbody()->AddForce(Vector3::UnitY * 2000.0f);
			}
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