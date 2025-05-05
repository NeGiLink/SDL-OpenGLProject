#pragma once
#include "StandardLibrary.h"
#include "Math.h"
#include "Collision.h"
#include "Component.h"
#include "Actor.h"
#include "BaseScene.h"
#include "PhysWorld.h"

//�I�u�W�F�N�g�ɃR���|�[�l���g���Ďg��Rigidbody
class Rigidbody : public Component
{
public:
	Rigidbody(class ActorObject* owner, int updateOrder = 100);
	//FixedUpdate�ŌĂяo��
	void	FixedUpdate(float deltaTime)override;

	//Getter
	//�d�̓t���O�̎Q��
	bool	IsUseGravity() { return mUseGravity; }
	//�͂�������֐�
	void	AddForce(Vector3 velocity);
	//mVelocity��Getter
	Vector3 GetVelocity() { return mVelocity; }
	//Setter
	//�d�̓t���O�̐؂�ւ�
	void	SetUseGravity(bool active) { mUseGravity = active; }
	//mVelocity��Setter
	void	SetVelocity(Vector3 velocity) { mVelocity = velocity; }
private:
	//�d�̓t���O
	bool	mUseGravity;
	//�d�̓X�P�[�����O
	float	mGravityScale;
	//����(1.0f = 1kg)
	float	mMass;
	//�ړ���
	Vector3 mVelocity;
	//�����镪�̗͂̕ϐ�
	Vector3 mForces = Vector3::Zero;
};

