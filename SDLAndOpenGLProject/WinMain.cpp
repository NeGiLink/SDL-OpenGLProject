#include "WinMain.h"
#include <algorithm>
#include "Renderer.h"
#include "AudioSystem.h"
#include "PhysWorld.h"
#include "Actor.h"
#include "UIScreen.h"
#include "HUD.h"
#include "MeshComponent.h"
#include "FollowActor.h"
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

WinMain::WinMain()
	:mRenderer(nullptr)
	, mAudioSystem(nullptr)
	, mPhysWorld(nullptr)
	, mGameState(EGameplay)
	, mUpdatingActors(false)
{

}

bool WinMain::Initialize()
{
	// Initialize SDL
	int sdlResult = SDL_Init(SDL_INIT_VIDEO);
	if (sdlResult < 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	// Create the renderer
	mRenderer = new Renderer(this);
	if (!mRenderer->Initialize(1280.0f, 800.0f))
	{
		SDL_Log("Failed to initialize renderer");
		delete mRenderer;
		mRenderer = nullptr;
		return false;
	}

	// Create the audio system
	mAudioSystem = new AudioSystem(this);
	if (!mAudioSystem->Initialize())
	{
		SDL_Log("Failed to initialize audio system");
		mAudioSystem->Shutdown();
		delete mAudioSystem;
		mAudioSystem = nullptr;
		return false;
	}

	// Create the physics world
	mPhysWorld = new PhysWorld(this);

	// Initialize SDL_ttf
	if (TTF_Init() < 0)
	{
		SDL_Log("Failed to initialize SDL_ttf");
		return false;
	}

	LoadData();

	mTicksCount = SDL_GetTicksNS();

	return true;
}

void WinMain::RunLoop()
{
	while (mGameState != EQuit)
	{
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

void WinMain::AddPlane(PlaneActor* plane)
{
	mPlanes.emplace_back(plane);
}

void WinMain::RemovePlane(PlaneActor* plane)
{
	auto iter = std::find(mPlanes.begin(), mPlanes.end(), plane);
	mPlanes.erase(iter);
}

void WinMain::ProcessInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_EVENT_QUIT:
			mGameState = EQuit;
			break;
			// This fires when a key's initially pressed
		case SDL_EVENT_KEY_DOWN:
			if (!event.key.repeat)
			{
				if (mGameState == EGameplay)
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
			if (mGameState == EGameplay)
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
	if (mGameState == EGameplay)
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
}

void WinMain::HandleKeyPress(int key)
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

void WinMain::UpdateGame()
{
	while ((SDL_GetTicksNS() - mTicksCount) < 16'000'000) // 16ms = 16,000,000ns
	;
	float deltaTime = (SDL_GetTicksNS() - mTicksCount) / 1'000'000'000.0f;

	// Clamp maximum delta time value
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}

	// Update tick counts (for next frame)
	mTicksCount = SDL_GetTicksNS();

	if (mGameState == EGameplay)
	{
		// Update all actors
		mUpdatingActors = true;
		for (auto actor : mActors)
		{
			actor->Update(deltaTime);
		}
		mUpdatingActors = false;

		// Move any pending actors to mActors
		for (auto pending : mPendingActors)
		{
			pending->ComputeWorldTransform();
			mActors.emplace_back(pending);
		}
		mPendingActors.clear();

		// Add any dead actors to a temp vector
		std::vector<ActorObject*> deadActors;
		for (auto actor : mActors)
		{
			if (actor->GetState() == ActorObject::EDead)
			{
				deadActors.emplace_back(actor);
			}
		}

		// Delete dead actors (which removes them from mActors)
		for (auto actor : deadActors)
		{
			delete actor;
		}
	}

	// Update audio system
	mAudioSystem->Update(deltaTime);

	// Update UI screens
	for (auto ui : mUIStack)
	{
		if (ui->GetState() == UIScreen::EActive)
		{
			ui->Update(deltaTime);
		}
	}
	// Delete any UIScreens that are closed
	auto iter = mUIStack.begin();
	while (iter != mUIStack.end())
	{
		if ((*iter)->GetState() == UIScreen::EClosing)
		{
			delete* iter;
			iter = mUIStack.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}

void WinMain::GenerateOutput()
{
	mRenderer->Draw();
}

void WinMain::LoadData()
{
	// Load English text
	LoadText("Assets/English.gptext");

	// Create actors
	ActorObject* a = nullptr;
	Quaternion q;
	//MeshComponent* mc = nullptr;

	// Setup floor
	const float start = -1250.0f;
	const float size = 250.0f;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			a = new PlaneActor(this);
			q = Quaternion(Vector3::UnitX, -Math::PiOver2);
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
	q = Quaternion(Vector3::UnitY, -Math::PiOver2);
	for (int i = 0; i < 10; i++)
	{
		a = new PlaneActor(this);
		a->SetPosition(Vector3(start - size, 0.0f, start + i * size));
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
	mRenderer->SetAmbientLight(Vector3(0.4f, 0.4f, 0.4f));
	DirectionalLight& dir = mRenderer->GetDirectionalLight();
	dir.mDirection = Vector3(0.0f, -0.707f, -0.707f);
	dir.mDiffuseColor = Vector3(0.78f, 0.88f, 1.0f);
	dir.mSpecColor = Vector3(0.8f, 0.8f, 0.8f);

	// UI elements
	mHUD = new HUD(this);


	// Start music
	mMusicEvent = mAudioSystem->PlayEvent("event:/Music");

	// Enable relative mouse mode for camera look
	SDL_SetWindowRelativeMouseMode(mRenderer->GetWindow(),true);
	// Make an initial call to get relative to clear out
	SDL_GetRelativeMouseState(nullptr, nullptr);

	// Different camera actors
	//mFollowActor = new FollowActor(this);
	mFPSActor = new FPSActor(this);

	a = new DiceActor(this);
	a->SetPosition(Vector3(-500.0f, 0.0f, 0.0f));

	a = new TwoObjectActor(this);
	a->SetPosition(Vector3(1000.0f,200.0f,0.0f));

	a = new YBotActor(this);

	a = new TestCharacter(this);


	// Create target actors
	q = Quaternion(Vector3::UnitY, Math::PiOver2);
	a = new TargetActor(this);
	a->SetPosition(Vector3(0.0f, 100.0f, 1450.0f));
	a = new TargetActor(this);
	a->SetPosition(Vector3(0.0f, 400.0f, 1450.0f));
	a = new TargetActor(this);
	a->SetPosition(Vector3(-500.0f, 200.0f, 1450.0f));
	a = new TargetActor(this);
	a->SetPosition(Vector3(500.0f, 200.0f, 1450.0f));
	a = new TargetActor(this);
	a->SetPosition(Vector3(-1450.0f, 200.0f, 0.0f));
	a->SetRotation(Quaternion(Vector3::UnitX, Math::PiOver2));
	a = new TargetActor(this);
	a->SetPosition(Vector3(1450.0f, 200.0f, 0.0f));
	a->SetRotation(Quaternion(Vector3::UnitX, -Math::PiOver2));
}

void WinMain::UnloadData()
{
	// Delete actors
	// Because ~Actor calls RemoveActor, have to use a different style loop
	while (!mActors.empty())
	{
		delete mActors.back();
	}

	// Clear the UI stack
	while (!mUIStack.empty())
	{
		delete mUIStack.back();
		mUIStack.pop_back();
	}

	if (mRenderer)
	{
		mRenderer->UnloadData();
	}

	// Unload fonts
	for (auto f : mFonts)
	{
		f.second->Unload();
		delete f.second;
	}

	// Unload skeletons
	for (auto s : mSkeletons)
	{
		delete s.second;
	}

	// Unload animators
	for (auto a : mAnimators) {
		delete a.second;
	}
}

void WinMain::Shutdown()
{
	UnloadData();
	TTF_Quit();
	delete mPhysWorld;
	if (mRenderer)
	{
		mRenderer->Shutdown();
	}
	if (mAudioSystem)
	{
		mAudioSystem->Shutdown();
	}
	SDL_Quit();
}

void WinMain::AddActor(ActorObject* actor)
{
	// If we're updating actors, need to add to pending
	if (mUpdatingActors)
	{
		mPendingActors.emplace_back(actor);
	}
	else
	{
		mActors.emplace_back(actor);
	}
}

void WinMain::RemoveActor(ActorObject* actor)
{
	// Is it in pending actors?
	auto iter = std::find(mPendingActors.begin(), mPendingActors.end(), actor);
	if (iter != mPendingActors.end())
	{
		// Swap to end of vector and pop off (avoid erase copies)
		std::iter_swap(iter, mPendingActors.end() - 1);
		mPendingActors.pop_back();
	}

	// Is it in actors?
	iter = std::find(mActors.begin(), mActors.end(), actor);
	if (iter != mActors.end())
	{
		// Swap to end of vector and pop off (avoid erase copies)
		std::iter_swap(iter, mActors.end() - 1);
		mActors.pop_back();
	}
}

void WinMain::PushUI(UIScreen* screen)
{
	mUIStack.emplace_back(screen);
}

Font* WinMain::GetFont(const std::string& fileName)
{
	auto iter = mFonts.find(fileName);
	if (iter != mFonts.end())
	{
		return iter->second;
	}
	else
	{
		Font* font = new Font(this);
		if (font->Load(fileName))
		{
			mFonts.emplace(fileName, font);
		}
		else
		{
			font->Unload();
			delete font;
			font = nullptr;
		}
		return font;
	}
}

void WinMain::LoadText(const std::string& fileName)
{
	// Clear the existing map, if already loaded
	mText.clear();
	// Try to open the file
	std::ifstream file(fileName);
	if (!file.is_open())
	{
		SDL_Log("Text file %s not found", fileName.c_str());
		return;
	}
	// Read the entire file to a string stream
	std::stringstream fileStream;
	fileStream << file.rdbuf();
	std::string contents = fileStream.str();
	// Open this file in rapidJSON
	rapidjson::StringStream jsonStr(contents.c_str());
	rapidjson::Document doc;
	doc.ParseStream(jsonStr);
	if (!doc.IsObject())
	{
		SDL_Log("Text file %s is not valid JSON", fileName.c_str());
		return;
	}
	// Parse the text map
	const rapidjson::Value& actions = doc["TextMap"];
	for (rapidjson::Value::ConstMemberIterator itr = actions.MemberBegin();
		itr != actions.MemberEnd(); ++itr)
	{
		if (itr->name.IsString() && itr->value.IsString())
		{
			mText.emplace(itr->name.GetString(),
				itr->value.GetString());
		}
	}
}

const std::string& WinMain::GetText(const std::string& key)
{
	static std::string errorMsg("**KEY NOT FOUND**");
	// Find this text in the map, if it exists
	auto iter = mText.find(key);
	if (iter != mText.end())
	{
		return iter->second;
	}
	else
	{
		return errorMsg;
	}
}

Skeleton* WinMain::GetSkeleton(const std::string& fileName)
{
	auto iter = mSkeletons.find(fileName);
	if (iter != mSkeletons.end())
	{
		return iter->second;
	}
	else
	{
		Skeleton* sk = new Skeleton();
		if (sk->Load(fileName))
		{
			mSkeletons.emplace(fileName, sk);
		}
		else
		{
			delete sk;
			sk = nullptr;
		}
		return sk;
	}
}

Animator* WinMain::GetAnimator(const std::string& fileName,class Animator* animator)
{
	auto iter = mAnimators.find(fileName);
	if (iter != mAnimators.end())
	{
		return iter->second;
	}
	else
	{
		mAnimators.emplace(fileName, animator);
		return animator;
	}
}
