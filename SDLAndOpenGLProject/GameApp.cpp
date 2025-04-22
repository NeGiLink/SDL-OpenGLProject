#include "GameApp.h"
#include "GameScene.h"
#include "WinMain.h"

BaseScene* GameApp::mActiveScene = nullptr;

GameApp::GameApp(GameWinMain* main) 
	:mWinMain(main)
{

}

bool GameApp::Initialize()
{
	mGameScene = new GameScene(mWinMain);

	mBaseScene = mGameScene;

	mActiveScene = mBaseScene;

	mBaseScene->Setup();

	mGameScene->Initialize();

	GameStateClass::SetGameState(GameState::EGameplay);

	return true;
}

bool GameApp::ProcessInput()
{
	mGameScene->InputUpdate();

	mBaseScene->ProcessInput();

	return true;
}

bool GameApp::Update()
{

	mGameScene->Update();

	mBaseScene->UpdateGame();

	return true;
}

bool GameApp::Release()
{
	mBaseScene->UnloadData();
	return true;
}