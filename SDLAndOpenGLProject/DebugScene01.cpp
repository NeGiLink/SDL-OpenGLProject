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

	// デバッグ用のステージ追加
	a = new DebugStageActor();
	Vector3 pos = Vector3(0.0f, 0.0f, 0.0f);
	a->SetPosition(pos);
	a = new DebugStageActor();
	pos = Vector3(0.0f, 10.0f, 10.0f);
	a->SetPosition(pos);
	q = Quaternion(Vector3::UnitX, -Math::PiOver2);
	a->SetRotation(q);

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


	Font* font = GetFont("Assets/Fonts/Carlito-Regular.ttf");
	//シーン名生成
	mSceneNameText = new Text(font, Vector2(500, 350));
	mSceneNameText->SetText("DebugScene1");
	mSceneNameText->SetFontSize(40);
	
	mPoseButtonText = new Text(font, Vector2(-550, 350));
	mPoseButtonText->SetText("Pose:ESC Key");
	mPoseButtonText->SetFontSize(40);

	mSceneLoadButtonText = new Text(font, Vector2(500, 150));
	mSceneLoadButtonText->SetText("LoadScene:L Key");
	mSceneLoadButtonText->SetFontSize(40);
	
	// Start music
	mMusicEvent = mAudioSystem->PlayEvent("event:/Music");

	// マウスカーソル位置を固定
	SDL_SetWindowRelativeMouseMode(mWinMain->GetRenderer()->GetWindow(), true);
	// マウスカーソルを非表示
	SDL_GetRelativeMouseState(nullptr, nullptr);

	// プレイヤー生成
	mFPSActor = new FPSActor();
	mFPSActor->SetPosition(Vector3(0.0f,1.0f,0.0f));

	mPlayer = mFPSActor;
	
	mCube = new CubeActor();
	mCube->SetPosition(Vector3(0.0f, 0.5f, 4.0f));
	
	mCapsule = new CapsuleActor();
	mCapsule->SetPosition(Vector3(2.0f, 0.5f, 4.0f));

	mSphere = new SphereActor();
	mSphere->SetPosition(Vector3(-2.0f, 0.5f, 4.0f));

	mDice = new DiceActor();
	mDice->SetPosition(Vector3(4.0f, 0.5f, 4.0f));

	// 的オブジェクト生成
	q = Quaternion();
	a = new TargetActor();
	a->SetPosition(Vector3(0.0f, 1.0f, 10.0f));
	a->SetRotation(q);
	a = new TargetActor();
	a->SetPosition(Vector3(0.0f, 4.0f, 10.0f));
	a->SetRotation(q);
	a = new TargetActor();
	a->SetPosition(Vector3(-5.0f, 2.0f, 10.0f));
	a->SetRotation(q);
	a = new TargetActor();
	a->SetPosition(Vector3(5.0f, 2.0f, 10.0f));
	a->SetRotation(q);
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
		case SDL_EVENT_QUIT:
			GameStateClass::SetGameState(GameState::GameEnd);
			break;
			// This fires when a key's initially pressed
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
		case SDL_EVENT_MOUSE_BUTTON_DOWN:
			if (GameStateClass::mGameState == GameState::GamePlay)
			{
				HandleKeyPress(event.button.button);
			}
			else if (!mUIStack.empty())
			{
				mUIStack.back()->
					HandleKeyPress(event.button.button);
			}
		default:
			break;
		}
	}
	const InputState& state = InputSystem::GetState();
	//const bool* state = SDL_GetKeyboardState(NULL);
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
	BaseScene::Update();
	return true;
}

void DebugScene01::HandleKeyPress(int key)
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
