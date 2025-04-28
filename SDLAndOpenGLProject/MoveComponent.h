#pragma once
#include "Component.h"
#include "Actor.h"

//�Q�l���Y�̃I�u�W�F�N�g�ړ��@�\
//���݂͖��g�p
class MoveComponent : public Component
{
public:
	// �X�V�̏����������čŏ��ɍX�V
	MoveComponent(class ActorObject* owner, int updateOrder = 10);
	void Update(float deltaTime) override;

	float GetAngularSpeed() const { return mAngularSpeed; }
	float GetForwardSpeed() const { return mForwardSpeed; }
	float GetStrafeSpeed() const { return mStrafeSpeed; }
	void SetAngularSpeed(float speed) { mAngularSpeed = speed; }
	void SetForwardSpeed(float speed) { mForwardSpeed = speed; }
	void SetStrafeSpeed(float speed) { mStrafeSpeed = speed; }
	void SetYSpeed(float speed) { mYSpeed = speed; }
private:
	float mAngularSpeed;
	float mForwardSpeed;
	float mStrafeSpeed;
	float mYSpeed;
};