#pragma once
#include "Component.h"
#include "Collision.h"
#include "Actor.h"
#include "BaseScene.h"
#include "PhysWorld.h"

//�R���C�_�[�̊��N���X
//�R���C�_�[�ɕK�v�ȏ��������Ă��܂��B
class Collider : public Component
{
protected:
	// ���[���h���OBB
	OBB						mWorldOBB;	

	AABB					mWorldBox;
	//�I�u�W�F�N�g���m�̓����蔻������邩���Ȃ���
	//Unity��Collider��Trigger����؂�ւ���t���O
	bool					mIsCollider = true;
	//�I�u�W�F�N�g�𓮂����Ȃ����������������߂�
	//Rigidbody�̂悤�ȋ@�\���Ȃ����ߒǉ�
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

	virtual const Sphere&	GetWorldSphere() const = 0;
	virtual const Capsule&	GetWorldCapsule() const = 0;
	virtual AABB			GetWorldAABBFromOBB() const { return mWorldBox; }

	virtual OBB				GetWorldOBB() const = 0;

	bool					IsCollider() { return mIsCollider; }
	void					SetCollider(bool active) { mIsCollider = active; }

	bool					IsStaticObject() { return mStaticObject; }
	void					SetStaticObject(bool active) { mStaticObject = active; }

	float					GetContactOffset() { return mContactOffset; }

};

