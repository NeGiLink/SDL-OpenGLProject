#include "DebugScene02.h"
#include "GameFunctions.h"

DebugScene02::DebugScene02(GameWinMain* winMain)
	:BaseScene(winMain)
{
}

bool DebugScene02::Initialize()
{
	BaseScene::Initialize();

	// ポイントライトメッシュをロードする
	//mWinMain->GetRenderer()->SetPointLightMesh(mWinMain->GetRenderer()->GetMesh("PointLight.gpmesh"));
	

	// 環境光の設定
	mWinMain->GetRenderer()->SetAmbientLight(Vector3(0.4f, 0.4f, 0.4f));
	DirectionalLight& dir = mWinMain->GetRenderer()->GetDirectionalLight();
	dir.mDirection = Vector3(0.0f, -0.707f, -0.707f);
	dir.mDiffuseColor = Vector3(0.78f, 0.88f, 1.0f);
	dir.mSpecColor = Vector3(0.8f, 0.8f, 0.8f);

	// Start music
	mMusicEvent = mAudioSystem->PlayEvent("event:/Music");

	// マウスカーソル位置を固定
	SDL_SetWindowRelativeMouseMode(mWinMain->GetRenderer()->GetWindow(), true);
	// マウスカーソルを非表示
	SDL_GetRelativeMouseState(nullptr, nullptr);

	// デバッグ用のステージ追加
	mStages01 = new Stages01();
	mStages01->Initialize();

	mTPSPlayer = new TPSPlayer();
	mTPSPlayer->SetLocalPosition(Vector3(0.0f, 0.5f, 0.0f));

	// プレイヤー生成
	mPlayer = mTPSPlayer;

	// ゲーム内のUI生成
	mTPSCanvas = new TPSCanvas();
	return true;
}

bool DebugScene02::InputUpdate(const InputState& state)
{
	BaseScene::InputUpdate(state);

	if (!mCanvasStack.empty())
	{
		mCanvasStack.back()->ProcessInput(state);
	}

	return true;
}

bool DebugScene02::Update()
{
	BaseScene::Update();
	return true;
}

void DebugScene02::HandleKeyPress(int key)
{
	switch (key)
	{
	case SDLK_ESCAPE:
		// Create pause menu
		new PauseMenu();
		break;
	case SDL_BUTTON_LEFT:
	{
		break;
	}
	default:
		break;
	}
	BaseScene::HandleKeyPress(key);
}