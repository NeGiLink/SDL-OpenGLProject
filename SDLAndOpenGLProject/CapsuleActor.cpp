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
	Capsule capsule(mPosition + Vector3(0,1.0f,0), mPosition + Vector3(0, -1.0f, 0), 0.5f);
	mCapsule->SetObjectCapsule(capsule);
}

void CapsuleActor::UpdateActor(float deltaTime)
{
}

void CapsuleActor::OnCollisionEnter(ActorObject* target)
{
	SDL_Log("Capsule Hit!");
	SDL_Log("Pos %.2f,%.2f,%.2f", mPosition.x, mPosition.y, mPosition.z);
}