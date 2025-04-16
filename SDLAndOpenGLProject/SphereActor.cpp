#include "SphereActor.h"
#include "WinMain.h"
#include "BaseScene.h"
#include "Renderer.h"
#include "MeshRenderer.h"
#include "SphereCollider.h"
#include "Mesh.h"

SphereActor::SphereActor(BaseScene* game)
	:ActorObject(game)
{
	MeshRenderer* mc = new MeshRenderer(this);
	Mesh* mesh = game->GetWinMain()->GetRenderer()->GetMesh("Sphere.fbx");
	mc->SetMesh(mesh);
	// Add collision Sphere
	mSphere = new SphereCollider(this);
	Sphere sphere(Vector3::Zero, 1.0f);
	mSphere->SetObjectSphere(sphere);

	SetScale(100.0f);
}

void SphereActor::UpdateActor(float deltaTime)
{
	mRecomputeWorldTransform = true;
	ComputeWorldTransform();
}

void SphereActor::OnCollisionEnter(ActorObject* target)
{
	SDL_Log("Sphere Hit!");
}
