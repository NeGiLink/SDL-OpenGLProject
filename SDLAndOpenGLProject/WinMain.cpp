#include "WinMain.h"
#include "Renderer.h"
#include <rapidjson/document.h>

// ここで定義（初期値を指定してもOK）
GameState GameStateClass::mGameState = GameState::EGameplay;

//TODO : 画面比率の変更箇所
float GameWinMain::mWindowWidth = 1280.0f;
float GameWinMain::mWindowHeight = 768.0f;

GameWinMain::GameWinMain()
	:mGameApp(nullptr)
{

}

bool GameWinMain::Initialize()
{
	// SDLの初期化
	int sdlResult = SDL_Init(SDL_INIT_VIDEO);
	if (sdlResult < 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	// Rendererの生成
	mRenderer = new Renderer(this);
	if (!mRenderer->Initialize(mWindowWidth, mWindowHeight))
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

void GameWinMain::RunLoop()
{
	while (GameStateClass::mGameState != GameState::EQuit)
	{
		Time::UpdateDeltaTime();
		mGameApp->ProcessInput();
		mGameApp->Update();
		GenerateOutput();
	}
}

void GameWinMain::GenerateOutput()
{
	mRenderer->Draw();
}

void GameWinMain::UnloadData()
{
	mGameApp->Release();
	if (mRenderer)
	{
		mRenderer->UnloadData();
	}
}

void GameWinMain::Shutdown()
{
	UnloadData();
	TTF_Quit();
	if (mRenderer)
	{
		mRenderer->Shutdown();
	}
	SDL_Quit();
}