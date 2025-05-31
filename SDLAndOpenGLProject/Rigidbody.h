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
private:
	//�d�̓t���O
	bool		mUseGravity;
	//�d�̓X�P�[�����O
	float		mGravityScale;
	//����(1.0f = 1kg)
	float		mMass;
	//�ړ���
	Vector3		mVelocity;
	//�����镪�̗͂̕ϐ�
	Vector3		mForces = Vector3::Zero;

	// 0�`1�F�Î~���C�W��
	float		mFriction;     

	// 0�`1�F�����W��
	float		mBounciness;   

	int			mSolverIterationCount;
public:
				Rigidbody(class ActorObject* owner, int updateOrder = 100);
	//FixedUpdate�ŌĂяo��
	void		FixedUpdate(float deltaTime)override;

	// velocity: ���݂̑��x
	// normalAxis: �Փ˂������iX/Y/Z�̂����ꂩ�j
	// �߂�l: �␳��̑��x
	Vector3 ResolveCollision(const Vector3& velocity, PhysWorld::Axis normalAxis) const;

	//Getter
	//�d�̓t���O�̎Q��
	bool		IsUseGravity() { return mUseGravity; }
	//�͂�������֐�
	void		AddForce(Vector3 velocity);
	//mVelocity��Getter
	Vector3		GetVelocity() { return mVelocity; }
	//Setter
	//�d�̓t���O�̐؂�ւ�
	void		SetUseGravity(bool active) { mUseGravity = active; }
	//mVelocity��Setter
	void		SetVelocity(Vector3 velocity) { mVelocity = velocity; }

	float		GetFriction() const { return mFriction; }
	void		SetFriction(float f) { mFriction = f; }

	float		GetBounciness() const { return mBounciness; }
	void		SetBounciness(float b) { mBounciness = b; }

	int			GetSolverIterationCount() const { return mSolverIterationCount; }
	void		SetSolverIterationCount(int count) { mSolverIterationCount = count; }
};