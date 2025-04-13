#include "DiceActor.h"
#include "WinMain.h"
#include "BaseScene.h"
#include "Renderer.h"
#include "MeshRenderer.h"
#include "BoxCollider.h"
#include "Mesh.h"

DiceActor::DiceActor(BaseScene* game)
	:ActorObject(game)
{
	SetScale(100.0f);
	SetRotation(Quaternion(Vector3::UnitY, Math::PiOver2 / 2));
	MeshRenderer* mc = new MeshRenderer(this);
	Mesh* mesh = game->GetWinMain()->GetRenderer()->GetMesh("TestCube.fbx");
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
}

void DiceActor::OnCollisionEnter(ActorObject* target)
{
	SDL_Log("Dice to Hit!");
}
