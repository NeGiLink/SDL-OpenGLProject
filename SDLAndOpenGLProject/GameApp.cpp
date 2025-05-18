#include "GameApp.h"

#include "DebugScene01.h"
#include "DebugScene02.h"


BaseScene* GameApp::mActiveScene = nullptr;

GameApp::GameApp(GameWinMain* main) 
	:mWinMain(main)
{

}

bool GameApp::Initialize()
{
	//�V�[������
	mDebugScene01 = new DebugScene01(mWinMain);
	mDebugScene02 = new DebugScene02(mWinMain);
	//�V�[�������X�g�ɒǉ�
	SceneManager::AddSceneList(mDebugScene01);
	SceneManager::AddSceneList(mDebugScene02);
	//�x�[�X�ɍŏ��̃V�[����ݒ�
	mActiveScene = mDebugScene01;
	//static�ȃV�[���Ƃ��ĕۑ�
	//mActiveScene = mBaseScene;
	//�V�[���̏�����
	if (!mActiveScene->Initialize())
	{
		return false;
	}
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
	mActiveScene->FixedUpdate();
	mActiveScene->Update();
	return true;
}

bool GameApp::Release()
{
	mActiveScene->UnloadData();
	return true;
}