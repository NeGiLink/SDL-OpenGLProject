#include "GameApp.h"
#include "GameScene.h"
#include "WinMain.h"

GameApp::GameApp(WinMain* main) 
	:mWinMain(main)
{

}

bool GameApp::Initialize()
{
	mGameScene = new GameScene(mWinMain);

	mBaseScene = mGameScene;

	mBaseScene->Setup();

	mGameScene->Initialize();

	GameStateClass::SetGameState(GameState::EGameplay);

	return true;
}

bool GameApp::Update()
{
	mBaseScene->ProcessInput();

	mGameScene->Update();

	mBaseScene->UpdateGame();

	return true;
}

bool GameApp::Release()
{
	mBaseScene->UnloadData();
	return true;
}