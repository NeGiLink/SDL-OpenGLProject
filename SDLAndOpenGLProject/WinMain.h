#pragma once
#include "SDOpenLib.h"

enum GameState
{
	GamePlay,
	TimeStop,
	GameEnd
};

class GameStateClass 
{
public:
	static void			SetGameState(GameState state) { mGameState = state; }
	static GameState	mGameState;
	static bool			mGameEventFrag;
};
//�Q�[���̕`�揈���Ǘ��N���X
//���Renderern�Ȃǂ̉�ʂ̍\�����Ǘ����Ă���N���X
class GameWinMain
{
private:
	//�Q�[�����̑S�Ă̕`����s���N���X
	void				Render();
	//�V�[���J�ڎ��̉������
	void				UnloadData();

	class Renderer*		mRenderer;

	//�Q�[��������
	GameApp*			mGameApp;
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
};