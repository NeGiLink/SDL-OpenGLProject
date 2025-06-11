#include "MeshActor.h"

void MeshActor::Load(string filePath)
{
	mMeshRenderer = new MeshRenderer(this);
	vector<class Mesh*> mesh = GetGame()->GetWinMain()->GetRenderer()->GetMeshs(filePath);
	mMeshRenderer->SetMeshs(mesh);
}

void MeshActor::SetTrigger(bool active)
{
	if (mBoxCollider)
	{
		mBoxCollider->SetStaticObject(active);
	}

	if (mSphereCollider)
	{
		mSphereCollider->SetStaticObject(active);
	}

	if (mCapsuleCollider)
	{
		mCapsuleCollider->SetStaticObject(active);
	}
}

void MeshActor::AddBoxCollider()
{
	BoxCollider* box = new BoxCollider(this);
	box->SetObjectBox(mMeshRenderer->GetMeshs()[0]->GetBoxs()[0]);
	box->SetObjectOBB(mMeshRenderer->GetMeshs()[0]->GetOBBBoxs()[0]);
	mBoxCollider = box;
}

void MeshActor::AddSphereCollider()
{
	SphereCollider* sphereCollider = new SphereCollider(this);
	Sphere sphere(mPosition,0.5f);
	sphereCollider->SetObjectSphere(sphere);

	mSphereCollider = sphereCollider;
}

void MeshActor::AddCapsuleCollider()
{
	OBB obb = mMeshRenderer->GetMeshs()[0]->GetOBBBoxs()[0];
	// ���S�Ɖ�]
	Vector3 center = obb.mCenter;
	Quaternion rot = obb.mRotation;

	// ���[�J��������
	Vector3 up = Vector3::Transform(Vector3::UnitY, rot); // ���[�J��Y���𐢊E��Ԃ�

	// ���a = X/Z�̏�������
	float radius = std::min(obb.mExtents.x, obb.mExtents.z);

	// �����̒��� = Y�������̒������痼�[�̔���������������
	float lineHalfLength = obb.mExtents.y - radius;

	// �n�_�E�I�_�𒆐S����㉺�ɉ��΂�
	Vector3 start = center - up * lineHalfLength;
	Vector3 end = center + up * lineHalfLength;

	Capsule capsule(start, end,radius);

	CapsuleCollider* capsuleCollider = new CapsuleCollider(this);
	capsuleCollider->SetObjectCapsule(capsule);
	mCapsuleCollider = capsuleCollider;
}
