#include "GameWinMain.h"

// ここで定義（初期値を指定してもOK）
GameState GameStateClass::mGameState = GameState::GamePlay;

bool GameStateClass::mGameEventFrag = false;

bool GameStateClass::mDebugFrag = false;

GameWinMain::GameWinMain()
	:mGameApp(nullptr)
	, mRenderer(nullptr)
{

}

GameWinMain::~GameWinMain()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL3_Shutdown();
	ImGui::DestroyContext();
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
	if (!mRenderer->Initialize(WindowRenderProperty::GetWidth(), WindowRenderProperty::GetHeight()))
	{
		Debug::ErrorLog("Failed to initialize Renderer");
		delete mRenderer;
		mRenderer = nullptr;
		return false;
	}

	// SDL_ttfの初期化
	if (!TTF_Init())
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

	//  ImGuiの初期化処理
	{
		//  バージョンの確認
		IMGUI_CHECKVERSION();

		//  コンテキストの作成
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // キーボードによるナビゲーションの有効化
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // コントローラーによるナビゲーションの有効化

		ImGui_ImplSDL3_InitForOpenGL(mRenderer->GetWindow(), mRenderer->GetContext());
		ImGui_ImplOpenGL3_Init("#version 330");
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
		
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL3_NewFrame();
		ImGui::NewFrame();

		//  デモウィンドウの描画
		ImGui::ShowDemoWindow();

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
		delete mRenderer;
	}
	delete mGameApp;
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
