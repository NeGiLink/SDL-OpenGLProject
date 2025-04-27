#pragma once
#include "Component.h"
#include "Collision.h"
#include "Actor.h"
#include "BaseScene.h"
#include "PhysWorld.h"

class Collider : public Component
{
public:
	Collider(class ActorObject* owner, int updateOrder = 100);
	~Collider();

	enum ColliderType
	{
		BoxType,
		SphereType,
		CapsuleType
	};
	virtual ColliderType GetType() = 0;
	virtual AABB GetWorldBox() const = 0;
	virtual const Sphere& GetWorldSphere() const = 0;
	virtual const Capsule& GetWorldCapsule() const = 0;

	bool IsCollider() { return collider; }
	void SetCollider(bool active) { collider = active; }

	bool IsStaticObject() { return staticObject; }
	void SetStaticObject(bool active) { staticObject = active; }
protected:
	AABB mWorldBox;
	//�I�u�W�F�N�g���m�̓����蔻������邩���Ȃ���
	//Unity��Collider��Trigger����؂�ւ���t���O
	bool collider = true;
	//�I�u�W�F�N�g�𓮂����Ȃ����������������߂�
	//Rigidbody�̂悤�ȋ@�\���Ȃ����ߒǉ�
	bool staticObject = true;
};

