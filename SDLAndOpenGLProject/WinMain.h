#pragma once
#include "FilePath.h"
#include "GameApp.h"
#include "PhysWorld.h"
#include "AudioSystem.h"
#include "SoundEvent.h"
#include "SceneManager.h"
#include "InputSystem.h"
#include "CallBackManager.h"

enum GameState
{
	GamePlay,
	TimeStop,
	GameEnd
};

class GameStateClass 
{
public:
	static void SetGameState(GameState state) { mGameState = state; }
	static GameState mGameState;
};
//�Q�[���̕`�揈���Ǘ��N���X
//���Renderern�Ȃǂ̉�ʂ̍\�����Ǘ����Ă���N���X
class GameWinMain
{
public:
						GameWinMain();
	//������
	bool				Initialize();
	//�Q�[������
	void				RunLoop();
	//�Q�[���I������
	void				Shutdown();
	//Renderer�̎擾
	class Renderer*		GetRenderer() { return mRenderer; }
private:
	//�Q�[�����̑S�Ă̕`����s���N���X
	void				Render();
	//�V�[���J�ڎ��̉������
	void				UnloadData();

	class Renderer*		mRenderer;

	//�Q�[��������
	GameApp*			mGameApp;
	//��ʃT�C�Y
	static float		mWindowWidth;

	static float		mWindowHeight;
};