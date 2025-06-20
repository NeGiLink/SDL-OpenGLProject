#include "DebugScene02.h"
#include "GameFunctions.h"

DebugScene02::DebugScene02(GameWinMain* winMain)
	:BaseScene(winMain)
{
}

bool DebugScene02::Initialize()
{
	BaseScene::Initialize();
	// Load English text
	LoadText("Assets/English.gptext");

	// Create actors
	ActorObject* a = nullptr;
	Quaternion q;

	// ポイントライトメッシュをロードする
	//mWinMain->GetRenderer()->SetPointLightMesh(mWinMain->GetRenderer()->GetMesh("PointLight.gpmesh"));
	

	// 環境光の設定
	mWinMain->GetRenderer()->SetAmbientLight(Vector3(0.4f, 0.4f, 0.4f));
	DirectionalLight& dir = mWinMain->GetRenderer()->GetDirectionalLight();
	dir.mDirection = Vector3(0.0f, -0.707f, -0.707f);
	dir.mDiffuseColor = Vector3(0.78f, 0.88f, 1.0f);
	dir.mSpecColor = Vector3(0.8f, 0.8f, 0.8f);
	
	// ゲーム内のUI生成
	mHUD = new HUD();


	Font* font = GetFont("NotoSansJP-Bold.ttf");
	//シーン名生成
	mSceneNameText = new Text(font, Vector2(500, 350));
	mSceneNameText->SetUTF_8Text(u8"DebugScene2");
	mSceneNameText->SetFontSize(40);

	mFrameRateText = new Text(font, Vector2(500, 250));
	float time = Time::gDeltaTime;
	mFrameRateText->SetText(std::to_string(time));
	mFrameRateText->SetFontSize(40);

	mPoseButtonText = new Text(font, Vector2(-550, 350));
	mPoseButtonText->SetUTF_8Text(u8"Pose:ESC");
	mPoseButtonText->SetFontSize(40);

	mSceneLoadButtonText = new Text(font, Vector2(500, 150));
	mSceneLoadButtonText->SetUTF_8Text(u8"LoadScene:K Key");
	mSceneLoadButtonText->SetFontSize(40);

	mTPoseButtonText = new Text(font, Vector2(-500, -350));
	mTPoseButtonText->SetUTF_8Text(u8"TPose:1");
	mTPoseButtonText->SetFontSize(40);

	mIdlePoseButtonText = new Text(font, Vector2(-300, -350));
	mIdlePoseButtonText->SetUTF_8Text(u8"IdlePose:2");
	mIdlePoseButtonText->SetFontSize(40);

	mRunPoseButtonText = new Text(font, Vector2(-100, -350));
	mRunPoseButtonText->SetUTF_8Text(u8"RunPose:3");
	mRunPoseButtonText->SetFontSize(40);

	mJumpPoseButtonText = new Text(font, Vector2(100, -350));
	mJumpPoseButtonText->SetUTF_8Text(u8"JumpPose:4");
	mJumpPoseButtonText->SetFontSize(40);

	mCapoeiraPoseButtonText = new Text(font, Vector2(300, -350));
	mCapoeiraPoseButtonText->SetUTF_8Text(u8"CapoeiraPose:5");
	mCapoeiraPoseButtonText->SetFontSize(40);

	// Start music
	mMusicEvent = mAudioSystem->PlayEvent("event:/Music");

	// マウスカーソル位置を固定
	SDL_SetWindowRelativeMouseMode(mWinMain->GetRenderer()->GetWindow(), true);
	// マウスカーソルを非表示
	SDL_GetRelativeMouseState(nullptr, nullptr);

	// デバッグ用のステージ追加
	mStages01 = new Stages01();
	mStages01->Initialize();


	q = Quaternion(Vector3::UnitY, Math::Pi);

	mTPSPlayer = new TPSPlayer();
	mTPSPlayer->SetLocalPosition(Vector3(0.0f, 0.5f, 0.0f));

	// プレイヤー生成
	mPlayer = mTPSPlayer;

	return true;
}

bool DebugScene02::InputUpdate(const InputState& state)
{
	BaseScene::InputUpdate(state);

	if (state.Keyboard.GetKeyDown(SDL_SCANCODE_K)) 
	{
		SceneManager::LoadScene(1);
	}
	else if (!mUIStack.empty())
	{
		mUIStack.back()->ProcessInput(state);
	}

	return true;
}

bool DebugScene02::Update()
{

	float time = Time::GetFrameRate();
	mFrameRateText->SetText("FPS : " + FloatToString::ToStringWithoutDecimal(time));

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