#include "WinMain.h"
#include "GameFunctions.h"

// �����Œ�`�i�����l���w�肵�Ă�OK�j
GameState GameStateClass::mGameState = GameState::GamePlay;

//TODO : ��ʔ䗦�̕ύX�ӏ�
float GameWinMain::mWindowWidth = 1280.0f;
float GameWinMain::mWindowHeight = 768.0f;

GameWinMain::GameWinMain()
	:mGameApp(nullptr)
{

}

bool GameWinMain::Initialize()
{
	// SDL�̏�����
	int sdlResult = SDL_Init(SDL_INIT_VIDEO);
	if (sdlResult < 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	// Renderer�̐���
	mRenderer = new Renderer(this);
	if (!mRenderer->Initialize(mWindowWidth, mWindowHeight))
	{
		SDL_Log("Failed to initialize renderer");
		delete mRenderer;
		mRenderer = nullptr;
		return false;
	}

	// SDL_ttf�̏�����
	if (TTF_Init() < 0)
	{
		SDL_Log("Failed to initialize SDL_ttf");
		return false;
	}

	Time::InitializeDeltaTime();

	mGameApp = new GameApp(this);
	mGameApp->Initialize();
	return true;
}

void GameWinMain::RunLoop()
{
	while (GameStateClass::mGameState != GameState::GameEnd)
	{
		Time::UpdateDeltaTime();
		//���[�h����
		mGameApp->LoadUpdate();
		//���͏���
		mGameApp->ProcessInput();
		//���W�X�V����
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
