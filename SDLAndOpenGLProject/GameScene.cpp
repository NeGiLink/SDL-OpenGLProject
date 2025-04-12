#include "GameScene.h"
#include <algorithm>
#include "Renderer.h"
#include "AudioSystem.h"
#include "PhysWorld.h"
#include "Actor.h"
#include "UIScreen.h"
#include "HUD.h"
#include "MeshRenderer.h"
#include "FPSActor.h"
#include "PlaneActor.h"
#include "TargetActor.h"
#include "BallActor.h"
#include "PauseMenu.h"
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include "Font.h"
#include <fstream>
#include <sstream>
#include <rapidjson/document.h>
#include "Skeleton.h"
#include "Animation.h"
#include "Animator.h"
#include "PointLightComponent.h"
#include "DiceActor.h"
#include "TwoObjectActor.h"
#include "TestCharacter.h"
#include "YBotActor.h"
#include "SmallCharacter.h"

#include "Image.h"
#include "Text.h"

GameScene::GameScene(WinMain* winMain)
	:BaseScene(winMain)
{
}

bool GameScene::Initialize()
{
	// Load English text
	LoadText("Assets/English.gptext");

	// Create actors
	ActorObject* a = nullptr;
	Quaternion q;

	// Setup floor
	const float start = -1250.0f;
	const float size = 250.0f;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			a = new PlaneActor(this);
			Vector3 pos = Vector3(start + j * size, -100.0f, start + i * size);
			a->SetPosition(pos);
			a->SetRotation(q);
			// Create some point lights
			a = new ActorObject(this);
			pos.y += 100.0f;
			a->SetPosition(pos);
			PointLightComponent* p = new PointLightComponent(a);
			Vector3 color;
			switch ((i + j) % 5)
			{
			case 0:
				color = Color::Green;
				break;
			case 1:
				color = Color::Blue;
				break;
			case 2:
				color = Color::Red;
				break;
			case 3:
				color = Color::Yellow;
				break;
			case 4:
				color = Color::LightPink;
				break;
			}
			p->mDiffuseColor = color;
			p->mInnerRadius = 100.0f;
			p->mOuterRadius = 200.0f;
		}
	}

	// Left/right walls
	q = Quaternion(Vector3::UnitZ, -Math::PiOver2);
	for (int i = 0; i < 10; i++)
	{
		a = new PlaneActor(this);
		a->SetPosition(Vector3(start - size, .0f, start + i * size));
		a->SetRotation(q);

		a = new PlaneActor(this);
		a->SetPosition(Vector3(-start + size, 0.0f, start + i * size));
		a->SetRotation(q);
	}


	q = Quaternion::Concatenate(q, Quaternion(Vector3::UnitY, Math::PiOver2));
	// Forward/back walls
	for (int i = 0; i < 10; i++)
	{

		a = new PlaneActor(this);
		a->SetPosition(Vector3(start + i * size, 0.0f, start - size));
		a->SetRotation(q);

		a = new PlaneActor(this);
		a->SetPosition(Vector3(start + i * size, 0.0f, -start + size));
		a->SetRotation(q);
	}

	// Setup lights
	mWinMain->GetRenderer()->SetAmbientLight(Vector3(0.4f, 0.4f, 0.4f));
	DirectionalLight& dir = mWinMain->GetRenderer()->GetDirectionalLight();
	dir.mDirection = Vector3(0.0f, -0.707f, -0.707f);
	dir.mDiffuseColor = Vector3(0.78f, 0.88f, 1.0f);
	dir.mSpecColor = Vector3(0.8f, 0.8f, 0.8f);

	// UI elements
	mHUD = new HUD(this);

	mTestText = new Text(this,GetFont("Assets/Fonts/Carlito-Regular.ttf"), Vector2(500, 350));
	float time = Time::deltaTime;
	mTestText->SetText(std::to_string(time));
	mTestText->SetFontSize(40);
	// Start music
	mMusicEvent = mAudioSystem->PlayEvent("event:/Music");

	// Enable relative mouse mode for camera look
	SDL_SetWindowRelativeMouseMode(mWinMain->GetRenderer()->GetWindow(), true);
	// Make an initial call to get relative to clear out
	SDL_GetRelativeMouseState(nullptr, nullptr);

	// Different camera actors
	mFPSActor = new FPSActor(this);

	mPlayer = mFPSActor;

	a = new DiceActor(this);
	a->SetPosition(Vector3(-500.0f, 0.0f, 500.0f));

	a = new TwoObjectActor(this);
	a->SetPosition(Vector3(1000.0f, 200.0f, 500.0f));

	a = new YBotActor(this);

	a = new TestCharacter(this);

	a = new SmallCharacter(this);


	// Create target actors
	q = Quaternion();
	a = new TargetActor(this);
	a->SetPosition(Vector3(0.0f, 100.0f, 1450.0f));
	a->SetRotation(q);
	a = new TargetActor(this);
	a->SetPosition(Vector3(0.0f, 400.0f, 1450.0f));
	a->SetRotation(q);
	a = new TargetActor(this);
	a->SetPosition(Vector3(-500.0f, 200.0f, 1450.0f));
	a->SetRotation(q);
	a = new TargetActor(this);
	a->SetPosition(Vector3(500.0f, 200.0f, 1450.0f));
	a->SetRotation(q);
	a = new TargetActor(this);
	a->SetPosition(Vector3(-1450.0f, 200.0f, 0.0f));
	a->SetRotation(Quaternion(Vector3::UnitY, Math::PiOver2));
	a = new TargetActor(this);
	a->SetPosition(Vector3(1450.0f, 200.0f, 0.0f));
	a->SetRotation(Quaternion(Vector3::UnitY, -Math::PiOver2));

	return true;
}

bool GameScene::Update()
{
	//“ü—Í‘€ì
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_EVENT_QUIT:
			GameStateClass::SetGameState(GameState::EQuit);
			break;
			// This fires when a key's initially pressed
		case SDL_EVENT_KEY_DOWN:
			if (!event.key.repeat)
			{
				if (GameStateClass::mGameState == GameState::EGameplay)
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
			if (GameStateClass::mGameState == GameState::EGameplay)
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

	const bool* state = SDL_GetKeyboardState(NULL);
	if (GameStateClass::mGameState == GameState::EGameplay)
	{
		for (auto actor : mActors)
		{
			if (actor->GetState() == ActorObject::EActive)
			{
				actor->ProcessInput(state);
			}
		}
	}
	else if (!mUIStack.empty())
	{
		mUIStack.back()->ProcessInput(state);
	}

	float time = Time::GetFrameRate();
	mTestText->SetText("FPS : " + FloatToString::ToStringWithoutDecimal(time));

	return false;
}

void GameScene::HandleKeyPress(int key)
{
	
	switch (key)
	{
	case SDLK_ESCAPE:
		// Create pause menu
		new PauseMenu(this);
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
}