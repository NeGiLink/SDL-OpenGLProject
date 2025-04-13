#include "BoxCollider.h"
#include "Actor.h"
#include "BaseScene.h"
#include "PhysWorld.h"

BoxCollider::BoxCollider(ActorObject* owner, int updateOrder)
	:Collider(owner, updateOrder)
	, mObjectBox(Vector3::Zero, Vector3::Zero)
	, mWorldBox(Vector3::Zero, Vector3::Zero)
	, mShouldRotate(true)
{
	mOwner->GetGame()->GetPhysWorld()->AddBox(this);
}

BoxCollider::~BoxCollider()
{
	mOwner->GetGame()->GetPhysWorld()->RemoveBox(this);
}

void BoxCollider::OnUpdateWorldTransform()
{
	// �I�u�W�F�N�g�{�b�N�X�Ƀ��Z�b�g����
	mWorldBox = mObjectBox;
	// Scale
	mWorldBox.mMin *= mOwner->GetScale();
	mWorldBox.mMax *= mOwner->GetScale();
	// Rotate (if we want to)
	if (mShouldRotate)
	{
		mWorldBox.Rotate(mOwner->GetRotation());
	}
	// Translate
	mWorldBox.mMin += mOwner->GetPosition();
	mWorldBox.mMax += mOwner->GetPosition();
}