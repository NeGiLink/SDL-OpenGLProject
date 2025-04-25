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
	//�V�[������
	mTitleScene = new TitleScene(mWinMain);
	mGameScene = new GameScene(mWinMain);
	//�V�[�������X�g�ɒǉ�
	SceneManager::AddSceneList(0, mTitleScene);
	SceneManager::AddSceneList(1, mGameScene);
	//�x�[�X�ɍŏ��̃V�[����ݒ�
	mBaseScene = mTitleScene;
	//static�ȃV�[���Ƃ��ĕۑ�
	mActiveScene = mBaseScene;
	//�V�[���̏�����
	mBaseScene->Setup();
	mBaseScene->Initialize();
	//�Q�[���̏�Ԃ�ݒ�
	GameStateClass::SetGameState(GameState::EGameplay);
	//Renderer�Ɍ��݂̃V�[����ݒ�
	mWinMain->GetRenderer()->SetBaseScene(mBaseScene);
	return true;
}

bool GameApp::ProcessInput()
{
	//���͍X�V
	mBaseScene->InputUpdate();

	mBaseScene->ProcessInput();

	return true;
}

bool GameApp::Update()
{
	//���[�h�t���O��true�Ȃ�
	if (SceneManager::IsLoading())
	{
		//���݂̃V�[���̃I�u�W�F�N�g�A�摜�Ȃǂ��A�����[�h
		mBaseScene->UnloadData();
		//Renderer�̂��̂��A�����[�h
		mWinMain->GetRenderer()->UnloadData();
		//�V�[����ύX
		mBaseScene = SceneManager::GetNowScene();
		//static���ύX
		mActiveScene = mBaseScene;
		//�V�����V�[���̏�����
		mBaseScene->Setup();
		mBaseScene->Initialize();
		//Renderer�̃V�[�����ύX
		mWinMain->GetRenderer()->SetBaseScene(mBaseScene);
		//���[�h�t���O������
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