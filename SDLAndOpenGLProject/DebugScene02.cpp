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
	mWinMain->GetRenderer()->SetPointLightMesh(mWinMain->GetRenderer()->GetMesh("PointLight.gpmesh"));
	

	// 環境光の設定
	mWinMain->GetRenderer()->SetAmbientLight(Vector3(0.4f, 0.4f, 0.4f));
	DirectionalLight& dir = mWinMain->GetRenderer()->GetDirectionalLight();
	dir.mDirection = Vector3(0.0f, -0.707f, -0.707f);
	dir.mDiffuseColor = Vector3(0.78f, 0.88f, 1.0f);
	dir.mSpecColor = Vector3(0.8f, 0.8f, 0.8f);
	
	// ゲーム内のUI生成
	mHUD = new HUD();


	Font* font = GetFont("Carlito-Regular.ttf");
	//シーン名生成
	mSceneNameText = new Text(font, Vector2(500, 350));
	mSceneNameText->SetText("DebugScene2");
	mSceneNameText->SetFontSize(40);

	mFrameRateText = new Text(font, Vector2(500, 250));
	float time = Time::gDeltaTime;
	mFrameRateText->SetText(std::to_string(time));
	mFrameRateText->SetFontSize(40);

	mPoseButtonText = new Text(font, Vector2(-550, 350));
	mPoseButtonText->SetText("Pose:ESC");
	mPoseButtonText->SetFontSize(40);

	mSceneLoadButtonText = new Text(font, Vector2(500, 150));
	mSceneLoadButtonText->SetText("LoadScene:K Key");
	mSceneLoadButtonText->SetFontSize(40);

	mTPoseButtonText = new Text(font, Vector2(-500, -350));
	mTPoseButtonText->SetText("TPose:1");
	mTPoseButtonText->SetFontSize(40);

	mIdlePoseButtonText = new Text(font, Vector2(-300, -350));
	mIdlePoseButtonText->SetText("IdlePose:2");
	mIdlePoseButtonText->SetFontSize(40);

	mRunPoseButtonText = new Text(font, Vector2(-100, -350));
	mRunPoseButtonText->SetText("RunPose:3");
	mRunPoseButtonText->SetFontSize(40);

	mJumpPoseButtonText = new Text(font, Vector2(100, -350));
	mJumpPoseButtonText->SetText("JumpPose:4");
	mJumpPoseButtonText->SetFontSize(40);

	mCapoeiraPoseButtonText = new Text(font, Vector2(300, -350));
	mCapoeiraPoseButtonText->SetText("CapoeiraPose:5");
	mCapoeiraPoseButtonText->SetFontSize(40);

	// Start music
	mMusicEvent = mAudioSystem->PlayEvent("event:/Music");

	// マウスカーソル位置を固定
	SDL_SetWindowRelativeMouseMode(mWinMain->GetRenderer()->GetWindow(), true);
	// マウスカーソルを非表示
	SDL_GetRelativeMouseState(nullptr, nullptr);

	// デバッグ用のステージ追加
	mDebugStage1 = new MeshActor();
	mDebugStage1->Load("DebugStage.fbx");
	Vector3 pos = Vector3(0.0f, 0.0f, 0.0f);
	mDebugStage1->SetLocalPosition(pos);
	mDebugStage1->SetActorTag(ActorTag::Ground);

	mDebugStage2 = new MeshActor();
	mDebugStage2->Load("DebugStage.fbx");
	pos = Vector3(0.0f, 10.0f, 10.0f);
	mDebugStage2->SetLocalPosition(pos);
	q = Quaternion(Vector3::UnitX, -Math::PiOver2);
	mDebugStage2->SetLocalRotation(q);

	mTestCharacter = new SkeletonMeshActor();
	mTestCharacter->Load("Paladin J Nordstrom.fbx");
	mTestCharacter->SetLocalPosition(Vector3(2.0f, 0.0f, 4.0f));

	mTestCharacter->SetAnimatorName("TestCharacter");
	mTestCharacter->GetAnimator()->Load("Idle.fbx", true);
	mTestCharacter->GetAnimator()->Load("Running.fbx", true);
	mTestCharacter->GetAnimator()->Load("Jumping.fbx");
	mTestCharacter->GetAnimator()->Load("Capoeira.fbx", true);
	mTestCharacter->GetAnimator()->Load("T-Pose.fbx", true);
	mTestCharacter->GetAnimator()->PlayAnimation(mTestCharacter->GetAnimator()->GetAnimations()[4]);


	q = Quaternion(Vector3::UnitY, Math::Pi);

	mTPSPlayer = new TPSPlayer();
	mTPSPlayer->SetLocalPosition(Vector3(0.0f,2.0f,0.0f));
	
	mSmallCharacter = new SkeletonMeshActor();
	mSmallCharacter->Load("goblin_d_shareyko.fbx");
	mSmallCharacter->SetLocalPosition(Vector3(-4.0f, 0.0f, 4.0f));
	mSmallCharacter->SetLocalRotation(Quaternion());

	mSmallCharacter->SetAnimatorName("SmallCharacter");
	mSmallCharacter->GetAnimator()->Load("Idle.fbx", true);
	mSmallCharacter->GetAnimator()->Load("Running.fbx", true);
	mSmallCharacter->GetAnimator()->Load("Jumping.fbx");
	mSmallCharacter->GetAnimator()->Load("Capoeira.fbx", true);
	mSmallCharacter->GetAnimator()->Load("T-Pose.fbx", true);
	mSmallCharacter->GetAnimator()->PlayAnimation(mSmallCharacter->GetAnimator()->GetAnimations()[4]);

	// プレイヤー生成
	mPlayer = mTPSPlayer;

	return true;
}

bool DebugScene02::InputUpdate()
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
	if (state.Keyboard.GetKeyDown(SDL_SCANCODE_K)) 
	{
		SceneManager::LoadScene(0);
	}
	else if (!mUIStack.empty())
	{
		mUIStack.back()->ProcessInput(state);
	}
	//テスト用：アニメーション切り替え
	if (state.Keyboard.GetKeyDown(KEY_1))
	{
		mTestCharacter->GetAnimator()->PlayBlendAnimation(mTestCharacter->GetAnimator()->GetAnimations()[4]);
		mSmallCharacter->GetAnimator()->PlayBlendAnimation(mSmallCharacter->GetAnimator()->GetAnimations()[4]);
	}
	else if (state.Keyboard.GetKeyDown(KEY_2))
	{
		mTestCharacter->GetAnimator()->PlayBlendAnimation(mTestCharacter->GetAnimator()->GetAnimations()[0]);
		mSmallCharacter->GetAnimator()->PlayBlendAnimation(mSmallCharacter->GetAnimator()->GetAnimations()[0]);
	}
	else if (state.Keyboard.GetKeyDown(KEY_3))
	{
		mTestCharacter->GetAnimator()->PlayBlendAnimation(mTestCharacter->GetAnimator()->GetAnimations()[1]);
		mSmallCharacter->GetAnimator()->PlayBlendAnimation(mSmallCharacter->GetAnimator()->GetAnimations()[1]);
	}
	else if (state.Keyboard.GetKeyDown(KEY_4))
	{
		mTestCharacter->GetAnimator()->PlayBlendAnimation(mTestCharacter->GetAnimator()->GetAnimations()[2]);
		mSmallCharacter->GetAnimator()->PlayBlendAnimation(mSmallCharacter->GetAnimator()->GetAnimations()[2]);
	}
	else if (state.Keyboard.GetKeyDown(KEY_5))
	{
		mTestCharacter->GetAnimator()->PlayBlendAnimation(mTestCharacter->GetAnimator()->GetAnimations()[3]);
		mSmallCharacter->GetAnimator()->PlayBlendAnimation(mSmallCharacter->GetAnimator()->GetAnimations()[3]);
	}

	BaseScene::InputUpdate();
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