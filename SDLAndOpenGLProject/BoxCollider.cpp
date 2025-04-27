#include "BoxCollider.h"


BoxCollider::BoxCollider(ActorObject* owner, int updateOrder)
	:Collider(owner, updateOrder)
	, mObjectBox(Vector3::Zero, Vector3::Zero)
	, mShouldRotate(true)
{

}

BoxCollider::~BoxCollider()
{

}

void BoxCollider::OnUpdateWorldTransform()
{
	// オブジェクトボックスにリセットする
	mWorldBox = mObjectBox;
	// Scale
	mWorldBox.mMin *= mOwner->GetLocalScale();
	mWorldBox.mMax *= mOwner->GetLocalScale();
	// Rotate (if we want to)
	if (mShouldRotate)
	{
		mWorldBox.Rotate(mOwner->GetLocalRotation());
	}
	// Translate
	mWorldBox.mMin += mOwner->GetLocalPosition();
	mWorldBox.mMax += mOwner->GetLocalPosition();
}