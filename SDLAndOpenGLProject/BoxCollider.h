#pragma once
#include "Collider.h"


//�{�b�N�X��Collider��ǉ�����R���|�[�l���g
class BoxCollider : public Collider
{
private:
	//���[�J�����AABB
	AABB			mObjectBox;

	// ���[�J�����OBB
	OBB				mObjectOBB;
	
	bool			mShouldRotate;
public:
					BoxCollider(class ActorObject* owner, int updateOrder = 100);
					~BoxCollider();

	void			OnUpdateWorldTransform() override;

	void			SetObjectBox(const AABB& model) { mObjectBox = model; }

	void			SetObjectOBB(const OBB& model) { mObjectOBB = model; }
	//AABB��Getter
	AABB			GetWorldBox() const override { return mWorldBox; }
	//OBB��Getter
	OBB				GetWorldOBB() const override { return mWorldOBB; }

	OBB				GetObjectOBB() const { return mObjectOBB; }
	//OBB����AABB�֕ϊ�
	AABB			GetWorldAABBFromOBB() const override;
	//Null
	const Sphere&	GetWorldSphere() const override
	{
		return Sphere(Vector3::Zero, 0.0f);
	}
	//Null
	const Capsule&	GetWorldCapsule() const override
	{
		return Capsule(Vector3::Zero, Vector3::Zero, 0.0f);
	}
	//��]�t���O
	void			SetShouldRotate(bool value) { mShouldRotate = value; }
	//�R���C�_�[�̃^�O
	ColliderType	GetType() override { return ColliderType::BoxType; }
};