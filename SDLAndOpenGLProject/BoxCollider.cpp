#include "BoxCollider.h"


BoxCollider::BoxCollider(ActorObject* owner, int updateOrder)
	:Collider(owner, updateOrder)
	, mObjectBox(Vector3::Zero, Vector3::Zero)
	, mObjectOBB(Vector3::Zero, Quaternion::Identity, Vector3::Zero)
	, mShouldRotate(true)
{
	// �P�ʃ{�b�N�X����Ƃ��� OBB
	mObjectOBB.mCenter = owner->GetPosition();
	mObjectOBB.mRotation = owner->GetRotation();
	mObjectOBB.mExtents = Vector3(0.5f, 0.5f, 0.5f); // 1x1x1�{�b�N�X�̔���
}

BoxCollider::~BoxCollider()
{

}

void BoxCollider::OnUpdateWorldTransform()
{
	//===OBB�̍X�V===
	// �X�P�[���A��]�A�ʒu���擾
	Vector3 scale = mOwner->GetScale();
	Quaternion rotation = mOwner->GetRotation();
	Vector3 position = mOwner->GetPosition();

	// ���[���h OBB ���\�z
	mWorldOBB.mCenter = position;
	mWorldOBB.mRotation = rotation;
	mWorldOBB.mExtents = mObjectOBB.mExtents * scale;

	//===AABB�̍X�V===
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

AABB BoxCollider::GetWorldAABBFromOBB() const
{
	const OBB& obb = mWorldOBB;

	Vector3 x = Vector3::Transform(Vector3::UnitX, obb.mRotation) * obb.mExtents.x;
	Vector3 y = Vector3::Transform(Vector3::UnitY, obb.mRotation) * obb.mExtents.y;
	Vector3 z = Vector3::Transform(Vector3::UnitZ, obb.mRotation) * obb.mExtents.z;

	Vector3 r = Vector3::Abs(x) + Vector3::Abs(y) + Vector3::Abs(z);
	return AABB(obb.mCenter - r, obb.mCenter + r);
}
