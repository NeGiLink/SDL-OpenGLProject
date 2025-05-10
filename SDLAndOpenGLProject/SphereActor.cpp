#include "SphereActor.h"

SphereActor::SphereActor()
	:ActorObject()
{
	MeshRenderer* mc = new MeshRenderer(this);
	vector<class Mesh*> mesh = GetGame()->GetWinMain()->GetRenderer()->GetMeshs("Sphere.fbx");
	mc->SetMeshs(mesh);
	// Add collision Sphere
	mSphere = new SphereCollider(this);
	Sphere sphere(mLocalPosition, 0.5f);
	mSphere->SetObjectSphere(sphere);
}
