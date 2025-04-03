#include "WinMain.h"
#include <algorithm>
#include "Renderer.h"
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <fstream>
#include <sstream>
#include <rapidjson/document.h>

#include "GameApp.h"

// ここで定義（初期値を指定してもOK）
GameState GameStateClass::mGameState = GameState::EGameplay;

WinMain::WinMain()
	:mGameApp(nullptr)
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

	// Initialize SDL_ttf
	if (TTF_Init() < 0)
	{
		SDL_Log("Failed to initialize SDL_ttf");
		return false;
	}

	Time::InitializeDeltaTime();

	mGameApp = new GameApp(this);
	mGameApp->Initialize();
	mRenderer->SetBaseScene(mGameApp->GetBaseScene());
	return true;
}

void WinMain::RunLoop()
{
	while (GameStateClass::mGameState != GameState::EQuit)
	{
		Time::UpdateDeltaTime();
		mGameApp->Update();
		GenerateOutput();
	}
}

void WinMain::GenerateOutput()
{
	mRenderer->Draw();
}

void WinMain::UnloadData()
{
	mGameApp->Release();
	if (mRenderer)
	{
		mRenderer->UnloadData();
	}
}

void WinMain::Shutdown()
{
	UnloadData();
	TTF_Quit();
	if (mRenderer)
	{
		mRenderer->Shutdown();
	}
	SDL_Quit();
}