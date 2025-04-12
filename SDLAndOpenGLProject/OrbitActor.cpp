#include "OrbitActor.h"
#include "MeshRenderer.h"
#include "WinMain.h"
#include "BaseScene.h"
#include "Renderer.h"
#include "OrbitCamera.h"
#include "MoveComponent.h"

OrbitActor::OrbitActor(BaseScene* game)
	:ActorObject(game)
{
	mMeshComp = new MeshRenderer(this);
	mMeshComp->SetMesh(game->GetWinMain()->GetRenderer()->GetMesh("RacingCar.gpmesh"));
	SetPosition(Vector3(0.0f, 0.0f, -100.0f));

	mCameraComp = new OrbitCamera(this);
}

void OrbitActor::ActorInput(const bool* keys)
{
	//マウス回転SDLからの相対的な動きを取得
	float x, y;
	Uint64 buttons = SDL_GetRelativeMouseState(&x, &y);
	// 右クリックが押されている場合にのみ回転を適用する
	if (buttons & SDL_BUTTON_MASK(SDL_BUTTON_RIGHT))
	{
		// マウスの動きは通常-500から+500の間であると仮定します。
		const int maxMouseSpeed = 500;
		// 最大速度での回転/秒
		const float maxOrbitSpeed = Math::Pi * 8;
		float yawSpeed = 0.0f;
		if (x != 0)
		{
			// [-1.0, 1.0]に変換する
			yawSpeed = static_cast<float>(x) / maxMouseSpeed;
			// 回転/秒で掛ける
			yawSpeed *= maxOrbitSpeed;
		}
		mCameraComp->SetYawSpeed(-yawSpeed);

		// 音高を計算する
		float pitchSpeed = 0.0f;
		if (y != 0)
		{
			// [-1.0, 1.0]に変換する
			pitchSpeed = static_cast<float>(y) / maxMouseSpeed;
			pitchSpeed *= maxOrbitSpeed;
		}
		mCameraComp->SetPitchSpeed(pitchSpeed);
	}
}

void OrbitActor::SetVisible(bool visible)
{
	mMeshComp->SetVisible(visible);
}