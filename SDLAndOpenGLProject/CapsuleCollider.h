#pragma once
#include "Collider.h"

//カプセル型のコライダークラス
class CapsuleCollider : public Collider
{
public:
	CapsuleCollider(class ActorObject* owner, int updateOrder = 100);
	~CapsuleCollider();

	void OnUpdateWorldTransform() override;

	void SetObjectCapsule(const Capsule& model) { mObjectCapsule = model; }
	//カプセルからAABBを取得
	AABB GetWorldBox() const override 
	{
		Vector3 min = Vector3::Min(mWorldCapsule.mSegment.mStart, mWorldCapsule.mSegment.mEnd) - Vector3(mWorldCapsule.mRadius, mWorldCapsule.mRadius, mWorldCapsule.mRadius);
		Vector3 max = Vector3::Max(mWorldCapsule.mSegment.mStart, mWorldCapsule.mSegment.mEnd) + Vector3(mWorldCapsule.mRadius, mWorldCapsule.mRadius, mWorldCapsule.mRadius);
		return AABB(min, max);
	}

	const Sphere& GetWorldSphere() const override
	{
		return Sphere(Vector3::Zero,0.0f);
	}

	const Capsule& GetWorldCapsule() const override
	{
		return mWorldCapsule;
	}

	void SetShouldRotate(bool value) { mShouldRotate = value; }

	ColliderType GetType() override { return ColliderType::CapsuleType; }
private:

	Capsule mObjectCapsule;
	
	Capsule mWorldCapsule;
	
	bool	mShouldRotate;
};