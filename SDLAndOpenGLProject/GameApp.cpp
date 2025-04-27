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
	//�V�[������
	mTitleScene = new TitleScene(mWinMain);
	mGameScene = new GameScene(mWinMain);
	//�V�[�������X�g�ɒǉ�
	SceneManager::AddSceneList(0, mTitleScene);
	SceneManager::AddSceneList(1, mGameScene);
	//�x�[�X�ɍŏ��̃V�[����ݒ�
	mActiveScene = mTitleScene;
	//static�ȃV�[���Ƃ��ĕۑ�
	//mActiveScene = mBaseScene;
	//�V�[���̏�����
	mActiveScene->Initialize();
	//�Q�[���̏�Ԃ�ݒ�
	GameStateClass::SetGameState(GameState::GamePlay);
	//Renderer�Ɍ��݂̃V�[����ݒ�
	mWinMain->GetRenderer()->SetBaseScene(mActiveScene);
	return true;
}

bool GameApp::ProcessInput()
{
	//���͍X�V
	mActiveScene->InputUpdate();

	return true;
}

bool GameApp::LoadUpdate()
{
	//���[�h�t���O��true�Ȃ�
	if (SceneManager::IsLoading())
	{
		//���݂̃V�[���̃I�u�W�F�N�g�A�摜�Ȃǂ��A�����[�h
		mActiveScene->UnloadData();
		//Renderer�̂��̂��A�����[�h
		mWinMain->GetRenderer()->UnloadData();
		//�V�[����ύX
		mActiveScene = SceneManager::GetNowScene();
		//static���ύX
		//mActiveScene = mBaseScene;
		//�V�����V�[���̏�����
		mActiveScene->Initialize();
		//Renderer�̃V�[�����ύX
		mWinMain->GetRenderer()->SetBaseScene(mActiveScene);
		//���[�h�t���O������
		SceneManager::DisabledLoading();
	}
	return true;
}

bool GameApp::Update()
{
	//���[�h�t���O��true�Ȃ�
	LoadUpdate();

	mActiveScene->Update();

	return true;
}

bool GameApp::Release()
{
	mActiveScene->UnloadData();
	return true;
}