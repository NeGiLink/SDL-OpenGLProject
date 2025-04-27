#include "GameApp.h"

#include "GameScene.h"
#include "TitleScene.h"


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
	mActiveScene = mTitleScene;
	//staticなシーンとして保存
	//mActiveScene = mBaseScene;
	//シーンの初期化
	mActiveScene->Initialize();
	//ゲームの状態を設定
	GameStateClass::SetGameState(GameState::GamePlay);
	//Rendererに現在のシーンを設定
	mWinMain->GetRenderer()->SetBaseScene(mActiveScene);
	return true;
}

bool GameApp::ProcessInput()
{
	//入力更新
	mActiveScene->InputUpdate();

	return true;
}

bool GameApp::LoadUpdate()
{
	//ロードフラグがtrueなら
	if (SceneManager::IsLoading())
	{
		//現在のシーンのオブジェクト、画像などをアンロード
		mActiveScene->UnloadData();
		//Rendererのものもアンロード
		mWinMain->GetRenderer()->UnloadData();
		//シーンを変更
		mActiveScene = SceneManager::GetNowScene();
		//staticも変更
		//mActiveScene = mBaseScene;
		//新しいシーンの初期化
		mActiveScene->Initialize();
		//Rendererのシーンも変更
		mWinMain->GetRenderer()->SetBaseScene(mActiveScene);
		//ロードフラグを解除
		SceneManager::DisabledLoading();
	}
	return true;
}

bool GameApp::Update()
{
	//ロードフラグがtrueなら
	LoadUpdate();

	mActiveScene->Update();

	return true;
}

bool GameApp::Release()
{
	mActiveScene->UnloadData();
	return true;
}