#pragma once
#include "Component.h"
#include "Collision.h"
#include "Actor.h"
#include "BaseScene.h"
#include "PhysWorld.h"

//コライダーの基底クラス
//コライダーに必要な情報を持っています。
class Collider : public Component
{
protected:
	AABB					mWorldBox;
	//オブジェクト同士の当たり判定をするかしないか
	//UnityのColliderかTriggerかを切り替えるフラグ
	bool					mCollider = true;
	//オブジェクトを動かさないか動かすかを決める
	//Rigidbodyのような機能がないため追加
	bool					mStaticObject = true;

	float					mContactOffset;
public:
							Collider(class ActorObject* owner, int updateOrder = 100);
							~Collider();

	enum ColliderType
	{
		BoxType,
		SphereType,
		CapsuleType
	};
	virtual ColliderType	GetType() = 0;
	virtual AABB			GetWorldBox() const = 0;
	virtual const Sphere&	GetWorldSphere() const = 0;
	virtual const Capsule&	GetWorldCapsule() const = 0;

	bool					IsCollider() { return mCollider; }
	void					SetCollider(bool active) { mCollider = active; }

	bool					IsStaticObject() { return mStaticObject; }
	void					SetStaticObject(bool active) { mStaticObject = active; }

	float					GetContactOffset() { return mContactOffset; }
};

