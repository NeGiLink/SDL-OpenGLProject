#pragma once
#include "Component.h"
#include "Actor.h"

//��{�I��WASD�̈ړ��ɑΉ������@�\
class BasicInputAction : public Component
{
public:
	// �X�V�̏����������čŏ��ɍX�V
	BasicInputAction(class ActorObject* owner, int updateOrder = 10);
	void FixedUpdate(float deltaTime)override;
	void Update(float deltaTime) override;
	//��{�I�Ȉړ�������s���֐�
	void MoveInputUpdate(const struct InputState& keys);
	//***Getter***
	//Z�����̈ړ���
	float GetForwardSpeed() const { return mForwardSpeed; }
	//X�����̈ړ���
	float GetStrafeSpeed() const { return mStrafeSpeed; }
	//***Setter***
	
	void SetForwardSpeed(float speed) { mForwardSpeed = speed; }
	
	void SetStrafeSpeed(float speed) { mStrafeSpeed = speed; }
	
	void AddJumpPower(float speed) { mJumpPower = speed; }

	bool GetJumping() { return mJumping; }

	void SetJumping(bool active) { mJumping = active; }
private:

	float	mForwardSpeed;
	
	float	mStrafeSpeed;
	
	float	mJumpPower;

	bool	mGravity;

	bool	mJumping;
};

