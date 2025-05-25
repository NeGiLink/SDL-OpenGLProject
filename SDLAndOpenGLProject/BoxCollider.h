#pragma once
#include "Collider.h"


//ボックスのColliderを追加するコンポーネント
class BoxCollider : public Collider
{
private:
	AABB			mObjectBox;
	
	bool			mShouldRotate;
public:
					BoxCollider(class ActorObject* owner, int updateOrder = 100);
					~BoxCollider();

	void			OnUpdateWorldTransform() override;

	void			SetObjectBox(const AABB& model) { mObjectBox = model; }
	AABB			GetWorldBox() const override { return mWorldBox; }

	const Sphere&	GetWorldSphere() const override
	{
		return Sphere(Vector3::Zero, 0.0f);
	}
	
	const Capsule&	GetWorldCapsule() const override
	{
		return Capsule(Vector3::Zero, Vector3::Zero, 0.0f);
	}
	
	void			SetShouldRotate(bool value) { mShouldRotate = value; }

	ColliderType	GetType() override { return ColliderType::BoxType; }
};