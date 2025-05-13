#pragma once
#include "Collider.h"
#include "Rigidbody.h"
#include "Transform.h"

class ColliderActor : public Transform
{
public:
	ColliderActor();
	virtual ~ColliderActor();
	//当たった時に呼び出される関数
	virtual void				OnCollisionEnter(class ActorObject* target){}
	//当たっている時に呼び出される関数
	virtual void				OnCollisionStay(class ActorObject* target) {}
	//当たり終わった時に呼び出される関数
	virtual void				OnCollisionExit(class ActorObject* target) {}

	virtual class Rigidbody* GetRigidbody() { return mRigidbody; }

	virtual class Collider* GetCollider() { return mCollider; }
protected:
	class Rigidbody* mRigidbody;

	class Collider* mCollider;
};

