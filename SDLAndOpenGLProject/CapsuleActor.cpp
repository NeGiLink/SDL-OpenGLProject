#include "CapsuleActor.h"
#include "WinMain.h"
#include "BaseScene.h"
#include "Renderer.h"
#include "MeshRenderer.h"
#include "CapsuleCollider.h"
#include "Mesh.h"

CapsuleActor::CapsuleActor(BaseScene* game)
	:ActorObject(game)
{
	MeshRenderer* mc = new MeshRenderer(this);
	Mesh* mesh = game->GetWinMain()->GetRenderer()->GetMesh("Capsule.fbx");
	mc->SetMesh(mesh);
	// Add collision Sphere
	mCapsule = new CapsuleCollider(this);
	Capsule capsule(Vector3(0,100.0f,0), Vector3(0, -100.0f, 0), 1.0f);
	mCapsule->SetObjectCapsule(capsule);

	SetScale(100.0f);
}

void CapsuleActor::UpdateActor(float deltaTime)
{
	mRecomputeWorldTransform = true;
	ComputeWorldTransform();
}

void CapsuleActor::OnCollisionEnter(ActorObject* target)
{
	SDL_Log("Capsule Hit!");
	SDL_Log("Pos %.2f,%.2f,%.2f", mPosition.x, mPosition.y, mPosition.z);
}