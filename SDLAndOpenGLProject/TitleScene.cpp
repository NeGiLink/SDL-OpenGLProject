#include "TitleScene.h"
#include "GameFunctions.h"

TitleScene::TitleScene(GameWinMain* winMain)
	:BaseScene(winMain)
{
}

bool TitleScene::Initialize()
{

	BaseScene::Initialize();
	// Load English text
	LoadText("Assets/English.gptext");

	// Create actors
	ActorObject* a = nullptr;
	Quaternion q;

	// Setup floor
	a = new PlaneActor();
	Vector3 pos = Vector3(0.0f, -1.5f, 0.0f);
	a->SetPosition(pos);
	a->SetRotation(Quaternion(Vector3::UnitX, Math::Pi));

	// ポイントライトメッシュをロードする
	mWinMain->GetRenderer()->SetPointLightMesh(mWinMain->GetRenderer()->GetMesh("PointLight.gpmesh"));

	// Setup lights
	mWinMain->GetRenderer()->SetAmbientLight(Vector3(0.4f, 0.4f, 0.4f));
	DirectionalLight& dir = mWinMain->GetRenderer()->GetDirectionalLight();
	dir.mDirection = Vector3(0.0f, -0.707f, -0.707f);
	dir.mDiffuseColor = Vector3(0.78f, 0.88f, 1.0f);
	dir.mSpecColor = Vector3(0.8f, 0.8f, 0.8f);
	// UI elements
	mHUD = new HUD();

	mTestText = new Text(GetFont("Assets/Fonts/CHI_Nohohon_free-R.ttf"), Vector2(500, 350));
	std::string name = "タイトル";
	mTestText->SetText("TitleScene");
	mTestText->SetFontSize(40);
	// Start music
	mMusicEvent = mAudioSystem->PlayEvent("event:/Music");

	// Enable relative mouse mode for camera look
	SDL_SetWindowRelativeMouseMode(mWinMain->GetRenderer()->GetWindow(), true);
	// Make an initial call to get relative to clear out
	SDL_GetRelativeMouseState(nullptr, nullptr);

	// Different camera actors
	mFPSActor = new FPSActor();

	mPlayer = mFPSActor;
	mCube = new CubeActor();
	mCube->SetPosition(Vector3(0.0f, -1.0f, 4.0f));
	
	/*
	mCapsule = new CapsuleActor();
	mCapsule->SetPosition(Vector3(2.0f, -1.0f, 4.0f));
	mCube->AddChildActor(mCapsule);
	mCapsule->SetPosition(Vector3(1.0f, 0.0f, 0.0f));

	mSphere = new SphereActor();
	mSphere->SetPosition(Vector3(-2.0f, -1.0f, 4.0f));

	mDice = new DiceActor();
	mDice->SetPosition(Vector3(0.0f, -1.0f, -4.0f));
	*/


	//a = new YBotActor();

	//a = new TestCharacter();

	//a = new SmallCharacter();

	// Create target actors
	q = Quaternion();
	a = new TargetActor();
	a->SetPosition(Vector3(0.0f, 1.0f, 14.5f));
	a->SetRotation(q);
	a = new TargetActor();
	a->SetPosition(Vector3(0.0f, 4.0f, 14.5f));
	a->SetRotation(q);
	a = new TargetActor();
	a->SetPosition(Vector3(-5.0f, 2.0f, 14.5f));
	a->SetRotation(q);
	a = new TargetActor();
	a->SetPosition(Vector3(5.0f, 2.0f, 14.5f));
	a->SetRotation(q);
	return true;
}

bool TitleScene::InputUpdate()
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

bool TitleScene::Update()
{
	BaseScene::Update();
	return true;
}

void TitleScene::HandleKeyPress(int key)
{
	switch (key)
	{
	case SDLK_ESCAPE:
		// Create pause menu
		//new PauseMenu();
		break;
	case '-':
	{
		// Reduce master volume
		float volume = mAudioSystem->GetBusVolume("bus:/");
		volume = Math::Max(0.0f, volume - 0.1f);
		mAudioSystem->SetBusVolume("bus:/", volume);
		break;
	}
	case '=':
	{
		// Increase master volume
		float volume = mAudioSystem->GetBusVolume("bus:/");
		volume = Math::Min(1.0f, volume + 0.1f);
		mAudioSystem->SetBusVolume("bus:/", volume);
		break;
	}
	case '1':
	{
		// Load English text
		LoadText("Assets/English.gptext");
		break;
	}
	case '2':
	{
		// Load Russian text
		LoadText("Assets/Russian.gptext");
		break;
	}
	case SDL_BUTTON_LEFT:
	{
		break;
	}
	default:
		break;
	}
	BaseScene::HandleKeyPress(key);
}
