#pragma once
#include "SoundEvent.h"
#include "Time.h"
#include "GameApp.h"

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

class WinMain
{
public:
	WinMain();
	bool Initialize();
	void RunLoop();
	void Shutdown();

	class Renderer* GetRenderer() { return mRenderer; }

	class GameApp* GetGameApp() { return mGameApp; }
private:
	void GenerateOutput();
	void UnloadData();

	class Renderer* mRenderer;

	//ƒQ[ƒ€“àˆ—
	GameApp* mGameApp;
};