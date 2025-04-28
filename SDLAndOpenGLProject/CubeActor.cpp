#include "CubeActor.h"

CubeActor::CubeActor()
	:ActorObject()
{
	MeshRenderer* mc = new MeshRenderer(this);
	Mesh* mesh = GetGame()->GetWinMain()->GetRenderer()->GetMesh("Cube.fbx");
	mc->SetMesh(mesh);
	// Add collision box
	for (unsigned int i = 0; i < mc->GetMeshs().size(); i++) {
		// ボックスの当たり判定機能追加
		for (unsigned int j = 0; j < mc->GetMeshs()[i]->GetBoxs().size(); j++)
		{
			BoxCollider* box = new BoxCollider(this);
			box->SetObjectBox(mc->GetMeshs()[i]->GetBoxs()[j]);
			mBoxs.push_back(box);
		}
	}

	mPushButtonMove = new PushButtonMove(this);
	mPushButtonMove->SetSpeed(0.5f);
}

void CubeActor::ActorInput(const InputState& keys)
{
	mPushButtonMove->MoveInputUpdate(keys);
}
