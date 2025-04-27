#pragma once

#include "GameApp.h"
#include "PhysWorld.h"
#include "AudioSystem.h"
#include "SoundEvent.h"
#include "SceneManager.h"
#include "InputSystem.h"

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
class GameWinMain
{
public:
	GameWinMain();
	bool Initialize();
	void RunLoop();
	void Shutdown();

	class Renderer* GetRenderer() { return mRenderer; }
private:
	void Render();
	void UnloadData();

	class Renderer* mRenderer;

	//�Q�[��������
	GameApp* mGameApp;
	//��ʃT�C�Y
	static float mWindowWidth;

	static float mWindowHeight;
};