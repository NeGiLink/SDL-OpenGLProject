#include "DiceActor.h"
#include "WinMain.h"
#include "Renderer.h"
#include "MeshComponent.h"
#include "BoxComponent.h"
#include "Mesh.h"

DiceActor::DiceActor(WinMain* game)
	:ActorObject(game)
{
	SetScale(100.0f);
	//SetRotation(Quaternion(Vector3::UnitZ, Math::Pi));
	MeshComponent* mc = new MeshComponent(this);
	Mesh* mesh = GetGame()->GetRenderer()->GetMesh("Assets/TestCube.fbx");
	mc->SetMesh(mesh);
	// Add collision box
	/*
	BoxComponent* bc = new BoxComponent(this);
	bc->SetObjectBox(mesh->GetBoxs());
	*/
}
