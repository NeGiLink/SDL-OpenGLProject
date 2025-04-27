#pragma once
#include "SDL3.h"
#include "Renderer.h"


class GameApp
{
public:
	GameApp(class GameWinMain* main);

	bool Initialize();

	bool ProcessInput();
	
	bool LoadUpdate();
	
	bool Update();
	
	bool Release();

	static class BaseScene* GetActiveScene() { return mActiveScene; }
private:

	static class BaseScene* mActiveScene;

	class GameScene* mGameScene;

	class TitleScene* mTitleScene;

	class GameWinMain* mWinMain;
};