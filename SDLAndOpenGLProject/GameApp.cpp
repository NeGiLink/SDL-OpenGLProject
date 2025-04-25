#include "GameApp.h"
#include "Renderer.h"
#include "GameScene.h"
#include "TitleScene.h"
#include "WinMain.h"

BaseScene* GameApp::mActiveScene = nullptr;

GameApp::GameApp(GameWinMain* main) 
	:mWinMain(main)
{

}

bool GameApp::Initialize()
{
	//シーン生成
	mTitleScene = new TitleScene(mWinMain);
	mGameScene = new GameScene(mWinMain);
	//シーンをリストに追加
	SceneManager::AddSceneList(0, mTitleScene);
	SceneManager::AddSceneList(1, mGameScene);
	//ベースに最初のシーンを設定
	mBaseScene = mTitleScene;
	//staticなシーンとして保存
	mActiveScene = mBaseScene;
	//シーンの初期化
	mBaseScene->Setup();
	mBaseScene->Initialize();
	//ゲームの状態を設定
	GameStateClass::SetGameState(GameState::EGameplay);
	//Rendererに現在のシーンを設定
	mWinMain->GetRenderer()->SetBaseScene(mBaseScene);
	return true;
}

bool GameApp::ProcessInput()
{
	//入力更新
	mBaseScene->InputUpdate();

	mBaseScene->ProcessInput();

	return true;
}

bool GameApp::Update()
{
	//ロードフラグがtrueなら
	if (SceneManager::IsLoading())
	{
		//現在のシーンのオブジェクト、画像などをアンロード
		mBaseScene->UnloadData();
		//Rendererのものもアンロード
		mWinMain->GetRenderer()->UnloadData();
		//シーンを変更
		mBaseScene = SceneManager::GetNowScene();
		//staticも変更
		mActiveScene = mBaseScene;
		//新しいシーンの初期化
		mBaseScene->Setup();
		mBaseScene->Initialize();
		//Rendererのシーンも変更
		mWinMain->GetRenderer()->SetBaseScene(mBaseScene);
		//ロードフラグを解除
		SceneManager::NoActiveLoading();
	}

	mBaseScene->Update();

	mBaseScene->UpdateGame();

	return true;
}

bool GameApp::Release()
{
	mBaseScene->UnloadData();
	return true;
}