#include "PlaneActor.h"

PlaneActor::PlaneActor()
	:ActorObject()
{
	mMeshComp = new MeshRenderer(this);
	mMeshComp->SetMeshs(GetGame()->GetWinMain()->GetRenderer()->GetMeshs("Plane.fbx"));

	AABB myBox(Vector3(-5.0f, -0.0f, -5.0f), Vector3(5.0f, 0.1f, 5.0f));
	BoxCollider* box = new BoxCollider(this);
	box->SetObjectBox(myBox);
	mBoxs.push_back(box);
	/*
	for (unsigned int i = 0; i < mMeshComp->GetMeshs().size(); i++) {
		// �{�b�N�X�̓����蔻��@�\�ǉ�
		for (unsigned int j = 0; j < mMeshComp->GetMeshs()[i]->GetBoxs().size(); j++)
		{
			BoxCollider* box = new BoxCollider(this);
			box->SetObjectBox(mMeshComp->GetMeshs()[i]->GetBoxs()[j]);
			mBoxs.push_back(box);
		}
	}
	*/
	//GetGame()->AddPlane(this);
}

PlaneActor::~PlaneActor()
{
	//GetGame()->RemovePlane(this);
}