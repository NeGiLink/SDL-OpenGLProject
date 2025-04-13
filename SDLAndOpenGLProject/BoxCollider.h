#pragma once
#include "Collision.h"
#include "Collider.h"

//ボックスのColliderを追加するコンポーネント
class BoxCollider : public Collider
{
public:
	BoxCollider(class ActorObject* owner, int updateOrder = 100);
	~BoxCollider();

	void OnUpdateWorldTransform() override;

	void SetObjectBox(const AABB& model) { mObjectBox = model; }
	const AABB& GetWorldBox() const { return mWorldBox; }

	void SetShouldRotate(bool value) { mShouldRotate = value; }

	ColliderType GetType() override { return ColliderType::Box; }
private:
	AABB mObjectBox;
	AABB mWorldBox;
	bool mShouldRotate;
};