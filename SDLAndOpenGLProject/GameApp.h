#pragma once
#include "SDL3.h"

class GameApp
{
public:
	GameApp(class GameWinMain* main);

	bool Initialize();
	bool ProcessInput();
	bool Update();
	bool Release();


	class BaseScene* GetBaseScene() { return mBaseScene; }

	static class BaseScene* GetActiveScene() { return mActiveScene; }
private:

	static class BaseScene* mActiveScene;

	class BaseScene* mBaseScene;

	class GameScene* mGameScene;

	class GameWinMain* mWinMain;
};