#include "SphereActor.h"

SphereActor::SphereActor()
	:ActorObject()
{
	MeshRenderer* mc = new MeshRenderer(this);
	Mesh* mesh = GetGame()->GetWinMain()->GetRenderer()->GetMesh("Sphere.fbx");
	mc->SetMesh(mesh);
	// Add collision Sphere
	mSphere = new SphereCollider(this);
	Sphere sphere(mLocalPosition, 0.5f);
	mSphere->SetObjectSphere(sphere);
}

void SphereActor::UpdateActor(float deltaTime)
{
}

void SphereActor::OnCollisionEnter(ActorObject* target)
{
	SDL_Log("Sphere Hit!");
}
