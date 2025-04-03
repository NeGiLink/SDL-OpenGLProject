#include "TargetActor.h"
#include "WinMain.h"
#include "BaseScene.h"
#include "Renderer.h"
#include "MeshRenderer.h"
#include "BoxComponent.h"
#include "Mesh.h"
#include "TargetComponent.h"

TargetActor::TargetActor(BaseScene* game)
	:ActorObject(game)
{
	//SetScale(10.0f);
	SetRotation(Quaternion(Vector3::UnitZ, Math::Pi));
	MeshRenderer* mc = new MeshRenderer(this);
	Mesh* mesh = game->GetWinMain()->GetRenderer()->GetMesh("Assets/Target.gpmesh");
	mc->SetMesh(mesh);
	// Add collision box
	/*
	BoxComponent* bc = new BoxComponent(this);
	bc->SetObjectBox(mesh->GetBox());
	new TargetComponent(this);
	*/

}