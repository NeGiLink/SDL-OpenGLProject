#pragma once
#include "BaseScene.h"
#include <unordered_map>
#include <string>
#include <vector>
#include "Math.h"
#include "SoundEvent.h"
#include <SDL3/SDL.h>
#include <stdint.h>
//ゲーム内の処理を行うクラス
class GameScene : public BaseScene
{
public:
	GameScene(class GameWinMain* winMain);
	
	bool Initialize();
	
	bool InputUpdate();

	bool Update();
	
	void HandleKeyPress(int key);

	class FPSActor* GetFPSPlayer() { return mFPSActor; }
private:
	// Game-specific code
	class FPSActor*					mFPSActor;

	class SphereActor* mSphere;

	class DiceActor* mDice;

	class CapsuleActor* mCapsule;
	
	std::vector<class PlaneActor*>	mPlanes;
	
	class SpriteComponent*			mCrosshair;
	
	SoundEvent						mMusicEvent;

	class Text*						mTestText;
};