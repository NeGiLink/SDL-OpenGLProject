#include "BaseCamera.h"
#include "Actor.h"
#include "Renderer.h"
#include "WinMain.h"
#include "BaseScene.h"
#include "AudioSystem.h"

BaseCamera::BaseCamera(ActorObject* owner, int updateOrder)
	:Component(owner, updateOrder)
{
	mGame->SetMainCamera(this);
}

void BaseCamera::SetViewMatrix(const Matrix4& view)
{
	// ビュー行列をレンダラーとオーディオシステムに渡す
	BaseScene* game = mOwner->GetGame();
	game->GetWinMain()->GetRenderer()->SetViewMatrix(view);
	game->GetAudioSystem()->SetListener(view);
}