#pragma once
#include "Collider.h"

/*
* ===�G���W����������/Engine internal processing===
*/

//�J�v�Z���^�̃R���C�_�[�N���X
class CapsuleCollider : public Collider
{
private:

	Capsule			mObjectCapsule;
	
	Capsule			mWorldCapsule;
	
	bool			mShouldRotate;
public:
					CapsuleCollider(class ActorObject* owner, int updateOrder = 100);
					~CapsuleCollider();

	void			OnUpdateWorldTransform() override;

	void			SetObjectCapsule(const Capsule& model) { mObjectCapsule = model; }

	OBB				GetWorldOBB() const override;

	const Sphere&	GetWorldSphere() const override { return Sphere(Vector3::Zero, 0.0f); }

	const Capsule&	GetWorldCapsule() const override { return mWorldCapsule; }

	void			SetShouldRotate(bool value) { mShouldRotate = value; }

	AABB			GetWorldAABBFromOBB() const override;

	ColliderType	GetType() override { return ColliderType::CapsuleType; }

};