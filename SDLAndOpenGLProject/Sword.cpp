#include "Sword.h"
#include "WinMain.h"
#include "BaseScene.h"
#include "Renderer.h"
#include "MeshRenderer.h"
#include "BoxComponent.h"
#include "Mesh.h"

Sword::Sword(BaseScene* game,Skeleton::Bone* rightHand)
	:ActorObject(game)
{
	SetScale(100.0f);
	//SetRotation(Quaternion(Vector3::UnitZ, Math::Pi));
	MeshRenderer* mc = new MeshRenderer(this);
	Mesh* mesh = game->GetWinMain()->GetRenderer()->GetMesh("Sword.fbx");
	mc->SetMesh(mesh);
	mRightHand = rightHand;
}

void Sword::UpdateRightHand(Skeleton::Bone* hand)
{
	SetPosition(hand->mLocalBindPose.mTranslation);
	SetRotation(hand->mLocalBindPose.mRotation);
}
