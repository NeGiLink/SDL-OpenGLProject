#pragma once
#include "SDL3.h"

class GameApp
{
public:
	GameApp(class WinMain* main);

	bool Initialize();
	bool Update();
	bool Release();


	class BaseScene* GetBaseScene() { return mBaseScene; }
private:

	class BaseScene* mBaseScene;

	class GameScene* mGameScene;

	class WinMain* mWinMain;
};