#pragma once
#include "Component.h"
#include "Actor.h"

//基本的なWASDの移動に対応した機能
class BasicInputAction : public Component
{
public:
	// 更新の順序を下げて最初に更新
	BasicInputAction(class ActorObject* owner, int updateOrder = 10);
	void Update(float deltaTime) override;
	//基本的な移動動作を行う関数
	void MoveInputUpdate(const struct InputState& keys);
	//一人称視点のカメラ処理を行いピッチ速度を取得する関数
	float CameraInputUpdate();
	//***Getter***
	//回転の移動量
	float GetAngularSpeed() const { return mAngularSpeed; }
	//Z方向の移動量
	float GetForwardSpeed() const { return mForwardSpeed; }
	//X方向の移動量
	float GetStrafeSpeed() const { return mStrafeSpeed; }
	//***Setter***
	void SetAngularSpeed(float speed) { mAngularSpeed = speed; }
	
	void SetForwardSpeed(float speed) { mForwardSpeed = speed; }
	
	void SetStrafeSpeed(float speed) { mStrafeSpeed = speed; }
	
	void AddJumpPower(float speed) { mJumpPower = speed; }

	bool GetJumping() { return mJumping; }

	void SetJumping(bool active) { mJumping = active; }
private:
	float	mAngularSpeed;

	float	mForwardSpeed;
	
	float	mStrafeSpeed;
	
	float	mJumpPower;

	bool	mGravity;

	bool	mJumping;
};

