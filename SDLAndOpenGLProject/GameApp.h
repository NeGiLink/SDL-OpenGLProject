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
private:

	class BaseScene* mBaseScene;

	class GameScene* mGameScene;

	class GameWinMain* mWinMain;
};