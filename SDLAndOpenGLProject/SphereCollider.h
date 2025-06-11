#pragma once
#include "Collider.h"

//����Collider��ǉ�����R���|�[�l���g
class SphereCollider : public Collider
{
private:

	Sphere			mObjectSphere;
	
	Sphere			mWorldSphere;
	
	bool			mShouldRotate;
public:
					SphereCollider(class ActorObject* owner, int updateOrder = 100);
					~SphereCollider();
	void			OnUpdateWorldTransform() override;

	void			SetObjectSphere(const Sphere& model) { mObjectSphere = model; }
	
	OBB				GetWorldOBB() const override;

	const Sphere&	GetWorldSphere() const override { return mWorldSphere; }

	const Capsule&	GetWorldCapsule() const override { return Capsule(Vector3::Zero, Vector3::Zero, 0.0f); }

	void			SetShouldRotate(bool value) { mShouldRotate = value; }

	AABB			GetWorldAABBFromOBB() const override;

	ColliderType	GetType() override { return ColliderType::SphereType; }

};