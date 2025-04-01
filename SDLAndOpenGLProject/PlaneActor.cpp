#include "PlaneActor.h"
#include "WinMain.h"
#include "Renderer.h"
#include "MeshComponent.h"
#include "BoxComponent.h"
#include "Mesh.h"

PlaneActor::PlaneActor(WinMain* game)
	:ActorObject(game)
{
	SetScale(10.0f);
	MeshComponent* mc = new MeshComponent(this);
	Mesh* mesh = GetGame()->GetRenderer()->GetMesh("Assets/Plane.gpmesh");
	mc->SetMesh(mesh);

	// Add collision box
	for (unsigned int i = 0; i < mesh->GetBoxs().size(); i++) 
	{
		BoxComponent* box = new BoxComponent(this);
		box->SetObjectBox(mesh->GetBoxs()[i]);
		mBoxs.push_back(box);
	}

	game->AddPlane(this);
}

PlaneActor::~PlaneActor()
{
	GetGame()->RemovePlane(this);
}