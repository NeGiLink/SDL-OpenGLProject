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
//ゲームの描画処理管理クラス
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

	//ゲーム内処理
	GameApp* mGameApp;
	//画面サイズ
	static float mWindowWidth;

	static float mWindowHeight;
};