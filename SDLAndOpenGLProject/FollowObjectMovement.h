#pragma once
#include "Component.h"
#include "Actor.h"
#include "BaseCamera.h"

class FollowObjectMovement : public Component
{
public:
	// 更新の順序を下げて最初に更新
	FollowObjectMovement(class ActorObject* owner, int updateOrder = 10);
	void FixedUpdate(float deltaTime)override;
	void Update(float deltaTime) override;
	//基本的な移動動作を行う関数
	void MoveInputUpdate(const struct InputState& keys);
	//***Getter***
	
	//***Setter***

	bool GetJumping() { return mJumping; }

	void SetJumping(bool active) { mJumping = active; }

private:

	float	mMaxSpeed;

	bool	mGravity;

	bool	mJumping;

	Vector3 mMoveForward;

	Vector3 mMoveRight;

	Vector3 mVelocity;

	Vector3 mInputDir;
};

