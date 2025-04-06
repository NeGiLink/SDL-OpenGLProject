#include "TwoObjectActor.h"
#include "WinMain.h"
#include "BaseScene.h"
#include "Renderer.h"
#include "MeshRenderer.h"
#include "BoxComponent.h"
#include "Mesh.h"

TwoObjectActor::TwoObjectActor(BaseScene* game)
	:ActorObject(game)
{
	SetScale(100.0f);
	MeshRenderer* mc = new MeshRenderer(this);
	mc->SetMeshs(game->GetWinMain()->GetRenderer()->GetMeshs("TwoCube.fbx"));
}

void TwoObjectActor::UpdateActor(float deltaTime)
{
}
