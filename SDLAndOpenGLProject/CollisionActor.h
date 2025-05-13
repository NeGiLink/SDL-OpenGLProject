#pragma once
#include "Collider.h"
#include "Rigidbody.h"
#include "Transform.h"

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

	virtual class Rigidbody* GetRigidbody() { return mRigidbody; }

	virtual class Collider* GetCollider() { return mCollider; }
protected:
	class Rigidbody* mRigidbody;

	class Collider* mCollider;
};

