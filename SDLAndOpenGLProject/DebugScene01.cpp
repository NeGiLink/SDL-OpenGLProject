#include "DebugScene01.h"
#include "GameFunctions.h"

DebugScene01::DebugScene01(GameWinMain* winMain)
	:BaseScene(winMain)
{
}

bool DebugScene01::Initialize()
{

	BaseScene::Initialize();
	// Load English text
	LoadText("Assets/English.gptext");

	// Create actors
	ActorObject* a = nullptr;
	Quaternion q;


	// ポイントライトメッシュをロードする
	mWinMain->GetRenderer()->SetPointLightMesh(mWinMain->GetRenderer()->GetMesh("PointLight.gpmesh"));

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
	mSceneNameText->SetText(u8"デバッグシーン1");
	mSceneNameText->SetFontSize(40);
	
	mPoseButtonText = new Text(font, Vector2(-500, 350));
	mPoseButtonText->SetText(u8"ポーズ:ESC Key");
	mPoseButtonText->SetFontSize(40);

	mSceneLoadButtonText = new Text(font, Vector2(450, 150));
	string t = u8"シーンのロード:L Key";
	mSceneLoadButtonText->SetText(t);
	mSceneLoadButtonText->SetFontSize(48);

	mFrameRateText = new Text(font, Vector2(500, 250));
	float time = Time::gDeltaTime;
	mFrameRateText->SetText(std::to_string(time));
	mFrameRateText->SetFontSize(40);
	
	// Start music
	mMusicEvent = mAudioSystem->PlayEvent("event:/Music3");

	// マウスカーソル位置を固定
	SDL_SetWindowRelativeMouseMode(mWinMain->GetRenderer()->GetWindow(), true);
	// マウスカーソルを非表示
	SDL_GetRelativeMouseState(nullptr, nullptr);

	// デバッグ用のステージ追加
	a = new DebugStageActor();
	Vector3 pos = Vector3(0.0f, 0.0f, 0.0f);
	a->SetLocalPosition(pos);
	a = new DebugStageActor();
	pos = Vector3(0.0f, 10.0f, 10.0f);
	a->SetLocalPosition(pos);
	q = Quaternion(Vector3::UnitX, -Math::PiOver2);
	a->SetLocalRotation(q);

	// プレイヤー生成
	mFPSActor = new FPSActor();
	mFPSActor->SetLocalPosition(Vector3(0.0f,1.0f,0.0f));

	mPlayer = mFPSActor;
	
	mCube = new CubeActor();
	mCube->SetLocalPosition(Vector3(0.0f, 0.5f, 4.0f));
	
	mCapsule = new CapsuleActor();
	mCapsule->SetLocalPosition(Vector3(2.0f, 2.0f, 4.0f));
	mCube->AddChildActor(mCapsule);


	mSphere = new SphereActor();
	mSphere->SetLocalPosition(Vector3(-2.0f, 0.5f, 4.0f));
	mCube->AddChildActor(mSphere);

	mDice = new DiceActor();
	mDice->SetLocalPosition(Vector3(4.0f, 0.5f, 4.0f));

	mDamageTrap = new DamageTrap();
	mDamageTrap->SetLocalPosition(Vector3(0.0f, 0.7f, -4.0f));
	mDamageTrap->SetActorTag(ActorTag::Enemy);

	mHealthObject = new HealthObject();
	mHealthObject->SetLocalPosition(Vector3(4.0f, 1.0f, -4.0f));
	mHealthObject->SetActorTag(ActorTag::Recovery);

	// 的オブジェクト生成
	q = Quaternion();
	a = new TargetActor();
	a->SetLocalPosition(Vector3(0.0f, 1.0f, 10.0f));
	a->SetLocalRotation(q);
	a = new TargetActor();
	a->SetLocalPosition(Vector3(0.0f, 4.0f, 10.0f));
	a->SetLocalRotation(q);
	a = new TargetActor();
	a->SetLocalPosition(Vector3(-5.0f, 2.0f, 10.0f));
	a->SetLocalRotation(q);
	a = new TargetActor();
	a->SetLocalPosition(Vector3(5.0f, 2.0f, 10.0f));
	a->SetLocalRotation(q);


	return true;
}

bool DebugScene01::InputUpdate()
{
	//入力操作
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			//実行が終了するとtrue
		case SDL_EVENT_QUIT:
			GameStateClass::SetGameState(GameState::GameEnd);
			break;
			// This fires when a key's initially pressed
			//キーボードのボタンをどれかを押すとtrue
		case SDL_EVENT_KEY_DOWN:
			if (!event.key.repeat)
			{
				if (GameStateClass::mGameState == GameState::GamePlay)
				{
					HandleKeyPress(event.key.key);
				}
				else if (!mUIStack.empty())
				{
					mUIStack.back()->
						HandleKeyPress(event.key.key);
				}
			}
			break;
			//マウスボタンのどれかを押すとtrue
		case SDL_EVENT_MOUSE_BUTTON_DOWN:
			if (!mUIStack.empty())
			{
				mUIStack.back()->
					HandleKeyPress(event.button.button);
			}
		default:
			break;
		}
	}
	const InputState& state = InputSystem::GetState();

	if (GameStateClass::mGameState == GameState::GamePlay)
	{
		for (auto actor : mActors)
		{
			if (actor->GetState() == ActorObject::EActive)
			{
				actor->ProcessInput(state);
			}
		}
	}

	if (state.Keyboard.GetKeyDown(KEY_O))
	{
		mMusicEvent.Pause();
	}
	else if (state.Keyboard.GetKeyDown(KEY_P))
	{
		mMusicEvent.Restart();
	}

	if (state.Keyboard.GetKeyDown(SDL_SCANCODE_L))
	{
		SceneManager::LoadScene(1);
	}
	else if (!mUIStack.empty())
	{
		mUIStack.back()->ProcessInput(state);
	}
	BaseScene::InputUpdate();
	return true;
}

bool DebugScene01::Update()
{
	float time = Time::GetFrameRate();
	mFrameRateText->SetText("FPS : " + FloatToString::ToStringWithoutDecimal(time));
	BaseScene::Update();
	return true;
}

void DebugScene01::HandleKeyPress(int key)
{
	switch (key)
	{
	case SDLK_ESCAPE:
		mPauseMenu = new PauseMenu();
		break;
	default:
		break;
	}
	BaseScene::HandleKeyPress(key);
}
