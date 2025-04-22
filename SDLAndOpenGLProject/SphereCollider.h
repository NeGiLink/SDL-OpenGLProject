#pragma once
#include "Collider.h"

//球のColliderを追加するコンポーネント
class SphereCollider : public Collider
{
public:
	SphereCollider(class ActorObject* owner, int updateOrder = 100);
	~SphereCollider();
	void OnUpdateWorldTransform() override;

	void SetObjectSphere(const Sphere& model) { mObjectSphere = model; }
	
	AABB GetWorldBox() const override 
	{
		Vector3 min = mWorldSphere.mCenter - mWorldSphere.mRadius;
		Vector3 max = mWorldSphere.mCenter + mWorldSphere.mRadius;
		return AABB(min, max);
	}
	const Sphere& GetWorldSphere() const override
	{
		return mWorldSphere;
	}
	const Capsule& GetWorldCapsule() const override 
	{
		return Capsule(Vector3::Zero, Vector3::Zero, 0.0f);
	}

	void SetShouldRotate(bool value) { mShouldRotate = value; }

	ColliderType GetType() override { return ColliderType::SphereType; }
private:
	Sphere mObjectSphere;
	Sphere mWorldSphere;
	bool mShouldRotate;
};