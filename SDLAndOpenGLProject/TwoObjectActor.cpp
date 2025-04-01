#include "TwoObjectActor.h"
#include "WinMain.h"
#include "Renderer.h"
#include "MeshComponent.h"
#include "BoxComponent.h"
#include "Mesh.h"

TwoObjectActor::TwoObjectActor(WinMain* game)
	:ActorObject(game)
{
	SetScale(100.0f);
	MeshComponent* mc = new MeshComponent(this);
	mc->SetMeshs(GetGame()->GetRenderer()->GetMeshs("Assets/TwoCube.fbx"));
}
