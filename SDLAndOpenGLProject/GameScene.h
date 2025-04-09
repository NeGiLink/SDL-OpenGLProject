#pragma once
#include "BaseScene.h"
#include <unordered_map>
#include <string>
#include <vector>
#include "Math.h"
#include "SoundEvent.h"
#include <SDL3/SDL.h>
#include <stdint.h>

class GameScene : public BaseScene
{
public:
	GameScene(class WinMain* winMain);
	bool Initialize();
	bool Update();
	void HandleKeyPress(int key);

	class FPSActor* GetFPSPlayer() { return mFPSActor; }
	class FollowActor* GetFollowPlayer() { return mFollowActor; }
private:
	// Game-specific code
	class FollowActor* mFollowActor;
	class FPSActor* mFPSActor;
	std::vector<class PlaneActor*> mPlanes;
	class SpriteComponent* mCrosshair;
	SoundEvent mMusicEvent;

	class Image* mTestImage;
	class Text* mTestText;
};