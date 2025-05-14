#pragma once
#include "Component.h"
#include "Actor.h"
//�{�^�������������ł̑���ɓ��������ړ��@�\
//���݂̓e�X�g�Ȃ̂Ŗ��L�[�ňړ�
class PushButtonMove : public Component
{
public:
	// �X�V�̏����������čŏ��ɍX�V
			PushButtonMove(class ActorObject* owner, int updateOrder = 10);
	void	Update(float deltaTime) override;
	//��{�I�Ȉړ�������s���֐�
	void	MoveInputUpdate(const struct InputState& keys);
	//***Setter***

	void	SetSpeed(float speed) { mSpeed = speed; }

	void	SetForwardSpeed(float speed) { mForwardSpeed = speed; }

	void	SetStrafeSpeed(float speed) { mStrafeSpeed = speed; }

	void	AddJumpPower(float speed) { mJumpPower = speed; }

	
private:
	//�㉺���E�Ŏg�p����ړ���
	float	mSpeed;

	float	mForwardSpeed;

	float	mStrafeSpeed;

	float	mJumpPower;
};

