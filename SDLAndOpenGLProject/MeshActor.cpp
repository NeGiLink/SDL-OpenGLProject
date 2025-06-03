#include "MeshActor.h"

void MeshActor::Load(string filePath)
{
	mMeshRenderer = new MeshRenderer(this);
	vector<class Mesh*> mesh = GetGame()->GetWinMain()->GetRenderer()->GetMeshs(filePath);
	mMeshRenderer->SetMeshs(mesh);

	// Add collision box
	for (unsigned int i = 0; i < mMeshRenderer->GetMeshs().size(); i++)
	{
		// ボックスの当たり判定機能追加
		for (unsigned int j = 0; j < mMeshRenderer->GetMeshs()[i]->GetBoxs().size(); j++)
		{
			BoxCollider* box = new BoxCollider(this);
			box->SetObjectBox(mMeshRenderer->GetMeshs()[i]->GetBoxs()[j]);
			mBoxs.push_back(box);
		}
	}
}

void MeshActor::SetTrigger(bool active)
{
	for (unsigned int i = 0; i < mMeshRenderer->GetMeshs().size(); i++)
	{
		for (unsigned int j = 0; j < mMeshRenderer->GetMeshs()[i]->GetBoxs().size(); j++)
		{
			mBoxs[i]->SetStaticObject(active);
		}
	}
}
