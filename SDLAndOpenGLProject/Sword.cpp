#include "Sword.h"
#include "WinMain.h"
#include "BaseScene.h"
#include "Renderer.h"
#include "MeshRenderer.h"
#include "BoxComponent.h"
#include "Mesh.h"

Sword::Sword(BaseScene* game)
	:ActorObject(game)
{
	SetScale(100.0f);
	//SetRotation(Quaternion(Vector3::UnitZ, Math::Pi));
	MeshRenderer* mc = new MeshRenderer(this);
	Mesh* mesh = game->GetWinMain()->GetRenderer()->GetMesh("Sword.fbx");
	mc->SetMesh(mesh);
}

void Sword::UpdateActor(float deltaTime)
{
	if (mParentActor) {
		SetPosition(mParentActor->GetPosition());
	}
}

void Sword::UpdateRightHand(Skeleton::Bone* hand)
{
	SetPosition(hand->mLocalBindPose.mPosition);
	SetRotation(hand->mLocalBindPose.mRotation);
}
