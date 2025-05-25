#include "WinMain.h"
#include "GameFunctions.h"

// ここで定義（初期値を指定してもOK）
GameState GameStateClass::mGameState = GameState::GamePlay;

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
	if (!mRenderer->Initialize(Window::Width, Window::Height))
	{
		Debug::ErrorLog("Failed to initialize Renderer");
		delete mRenderer;
		mRenderer = nullptr;
		return false;
	}

	// SDL_ttfの初期化
	if (TTF_Init() < 0)
	{
		Debug::ErrorLog("Failed to initialize SDL_ttf");
		return false;
	}

	Time::InitializeDeltaTime();

	mGameApp = new GameApp(this);
	if (!mGameApp->Initialize())
	{
		Debug::ErrorLog("Failed to initialize GameScenes");
		return false;
	}
	return true;
}

void GameWinMain::RunLoop()
{
	while (GameStateClass::mGameState != GameState::GameEnd)
	{
		Time::UpdateDeltaTime();
		//ロード処理
		mGameApp->LoadUpdate();
		//入力処理
		mGameApp->ProcessInput();
		//座標更新処理
		mGameApp->Update();
		Render();
	}
}

void GameWinMain::Render()
{
	mRenderer->Draw();
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

void GameWinMain::UnloadData()
{
	mGameApp->Release();
	if (mRenderer)
	{
		mRenderer->UnloadData();
	}
}
