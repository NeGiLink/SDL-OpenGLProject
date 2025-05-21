#include "Health.h"

HealthObject::HealthObject()
	:ActorObject()
{
	MeshRenderer* mc = new MeshRenderer(this);
	vector<class Mesh*> mesh = GetGame()->GetWinMain()->GetRenderer()->GetMeshs("Health.fbx");
	mc->SetMeshs(mesh);
	// Add collision box
	for (unsigned int i = 0; i < mc->GetMeshs().size(); i++)
	{
		// �{�b�N�X�̓����蔻��@�\�ǉ�
		for (unsigned int j = 0; j < mc->GetMeshs()[i]->GetBoxs().size(); j++)
		{
			BoxCollider* box = new BoxCollider(this);
			box->SetObjectBox(mc->GetMeshs()[i]->GetBoxs()[j]);
			box->SetStaticObject(false);
			mBoxs.push_back(box);
		}
	}
	SetLocalScale(0.5f);
}

void HealthObject::UpdateActor(float deltaTime)
{
	//�ȈՓI��Y����]����
	mRotationAmountY += 5 * deltaTime;
	Quaternion r = Quaternion(Vector3::UnitY, mRotationAmountY);
	SetLocalRotation(r);
}
