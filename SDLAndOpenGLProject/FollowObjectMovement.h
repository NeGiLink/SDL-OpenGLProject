#pragma once
#include "Component.h"
#include "Actor.h"
#include "BaseCamera.h"

//�O�l�̗p�̃I�u�W�F�N�g�̈ړ�����
class FollowObjectMovement : public Component
{
public:
	// �X�V�̏����������čŏ��ɍX�V
	FollowObjectMovement(class ActorObject* owner, int updateOrder = 10);
	void FixedUpdate(float deltaTime)override;
	void Update(float deltaTime) override;
	//��{�I�Ȉړ�������s���֐�
	void MoveInputUpdate(const struct InputState& keys);
	//***Getter***
	bool IsJumping() { return mJumping; }
	
	Vector3 GetInputDirection() { return mInputDirection; }

	//***Setter***
	void SetJumping(bool active) { mJumping = active; }


private:
	//�ړ��X�s�[�h
	float	mMaxSpeed;
	
	bool	mGravity;

	bool	mJumping;

	Vector3 mVelocity;

	Vector3 mInputDirection;
};

