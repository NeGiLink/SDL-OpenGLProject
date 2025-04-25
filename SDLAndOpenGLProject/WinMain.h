#pragma once
#include "SoundEvent.h"
#include "Time.h"
#include "GameApp.h"
#include "SceneManager.h"
#include "InputSystem.h"

enum GameState
{
	EGameplay,
	EPaused,
	EQuit
};

class GameStateClass 
{
public:
	static void SetGameState(GameState state) { mGameState = state; }
	static GameState mGameState;
};

class GameWinMain
{
public:
	GameWinMain();
	bool Initialize();
	void RunLoop();
	void Shutdown();

	class Renderer* GetRenderer() { return mRenderer; }

	class GameApp* GetGameApp() { return mGameApp; }
private:
	void GenerateOutput();
	void UnloadData();

	class Renderer* mRenderer;

	//ÉQÅ[ÉÄì‡èàóù
	GameApp* mGameApp;

	static float mWindowWidth;

	static float mWindowHeight;
};