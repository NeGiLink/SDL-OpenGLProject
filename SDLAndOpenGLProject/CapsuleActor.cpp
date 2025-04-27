#include "CapsuleActor.h"

CapsuleActor::CapsuleActor()
	:ActorObject()
{
	MeshRenderer* mc = new MeshRenderer(this);
	Mesh* mesh = GetGame()->GetWinMain()->GetRenderer()->GetMesh("Capsule.fbx");
	mc->SetMesh(mesh);

	// Add collision Sphere
	mCapsule = new CapsuleCollider(this);
	Capsule capsule(Vector3(0,1.0f,0), Vector3(0, -1.0f, 0), 0.5f);
	mCapsule->SetObjectCapsule(capsule);

}

void CapsuleActor::UpdateActor(float deltaTime)
{
}

void CapsuleActor::OnCollisionEnter(ActorObject* target)
{
	SDL_Log("Capsule Hit!");
	SDL_Log("Pos %.2f,%.2f,%.2f", mLocalPosition.x, mLocalPosition.y, mLocalPosition.z);
}