#include "CameraComponent.h"
#include "Actor.h"
#include "Renderer.h"
#include "WinMain.h"
#include "BaseScene.h"
#include "AudioSystem.h"

CameraComponent::CameraComponent(ActorObject* owner, int updateOrder)
	:Component(owner, updateOrder)
{
}

void CameraComponent::SetViewMatrix(const Matrix4& view)
{
	// Pass view matrix to renderer and audio system
	BaseScene* game = mOwner->GetGame();
	game->GetWinMain()->GetRenderer()->SetViewMatrix(view);
	game->GetAudioSystem()->SetListener(view);
}