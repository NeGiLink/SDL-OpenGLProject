#pragma once
#include "Collider.h"
#include "Rigidbody.h"
#include "Transform.h"

//�����蔻��A���������̃N���X���܂Ƃ߂�ActorObject�N���X
//���݂͖��g�p
class ColliderActor : public Transform
{
public:
	ColliderActor();
	virtual ~ColliderActor();
	//�����������ɌĂяo�����֐�
	virtual void				OnCollisionEnter(class ActorObject* target){}
	//�������Ă��鎞�ɌĂяo�����֐�
	virtual void				OnCollisionStay(class ActorObject* target) {}
	//������I��������ɌĂяo�����֐�
	virtual void				OnCollisionExit(class ActorObject* target) {}

	virtual class Rigidbody*	GetRigidbody() { return mRigidbody; }

	virtual class Collider*		GetCollider() { return mCollider; }
protected:
	//���������Ǘ��N���X
	class Rigidbody*			mRigidbody;
	//�����蔻��N���X
	class Collider*				mCollider;
};

