#include "DiceActor.h"
#include "WinMain.h"
#include "BaseScene.h"
#include "Renderer.h"
#include "MeshRenderer.h"
#include "BoxComponent.h"
#include "Mesh.h"

DiceActor::DiceActor(BaseScene* game)
	:ActorObject(game)
{
	SetScale(100.0f);
	MeshRenderer* mc = new MeshRenderer(this);
	Mesh* mesh = game->GetWinMain()->GetRenderer()->GetMesh("TestCube.fbx");
	mc->SetMesh(mesh);
	// Add collision box
	/*
	BoxComponent* bc = new BoxComponent(this);
	bc->SetObjectBox(mesh->GetBoxs());
	*/
}
