#include "PlaneActor.h"
#include "BaseScene.h"
#include "WinMain.h"
#include "Renderer.h"
#include "MeshRenderer.h"
#include "BoxComponent.h"
#include "Mesh.h"

PlaneActor::PlaneActor(BaseScene* game)
	:ActorObject(game)
{
	SetScale(50.0f);
	mMeshComp = new MeshRenderer(this);
	mMeshComp->SetMeshs(game->GetWinMain()->GetRenderer()->GetMeshs("Plane.fbx"));

	for (unsigned int i = 0; i < mMeshComp->GetMeshs().size(); i++) {
		// ボックスの当たり判定機能追加
		for (unsigned int j = 0; j < mMeshComp->GetMeshs()[i]->GetBoxs().size(); j++)
		{
			BoxComponent* box = new BoxComponent(this);
			box->SetObjectBox(mMeshComp->GetMeshs()[i]->GetBoxs()[j]);
			mBoxs.push_back(box);
		}
	}

	game->AddPlane(this);
}

PlaneActor::~PlaneActor()
{
	GetGame()->RemovePlane(this);
}