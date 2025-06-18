#include "GameApp.h"

#include "TitleScene.h"
#include "DebugScene01.h"
#include "DebugScene02.h"


BaseScene* GameApp::mActiveScene = nullptr;

GameApp::GameApp(GameWinMain* main) 
	:mWinMain(main)
{

}

bool GameApp::Initialize()
{
	//シーン生成
	mTitleScene = new TitleScene(mWinMain);
	mDebugScene01 = new DebugScene01(mWinMain);
	mDebugScene02 = new DebugScene02(mWinMain);
	//シーンをリストに追加
	SceneManager::AddSceneList(mTitleScene);
	SceneManager::AddSceneList(mDebugScene01);
	SceneManager::AddSceneList(mDebugScene02);
	//ベースに最初のシーンを設定
	mActiveScene = mTitleScene;
	//シーンの初期化
	if (!mActiveScene->Initialize())
	{
		return false;
	}
	//ゲームの状態を設定
	GameStateClass::SetGameState(GameState::GamePlay);
	//Rendererに現在のシーンを設定
	mWinMain->GetRenderer()->SetBaseScene(mActiveScene);
	return true;
}

bool GameApp::ProcessInput()
{
	const InputState& state = InputSystem::GetState();
	InputSystem::Update();
	//入力更新
	mActiveScene->InputUpdate(state);
	InputSystem::PrepareForUpdate();
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
		GameStateClass::SetGameState(GameState::GamePlay);
		//staticも変更
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
	mActiveScene->FixedUpdate();
	mActiveScene->Update();
	return true;
}

bool GameApp::Release()
{
	mActiveScene->UnloadData();
	return true;
}