#pragma once
#include "BaseScene.h"
#include "Math.h"
#include "SoundEvent.h"

//ゲーム内の処理を行うクラス
class GameScene : public BaseScene
{
public:
	GameScene(class GameWinMain* winMain);
	
	bool Initialize()override;
	
	bool InputUpdate()override;

	bool Update()override;
	
	void HandleKeyPress(int key)override;

	class FPSActor* GetFPSPlayer() { return mFPSActor; }
private:
	// Game-specific code
	class FPSActor*					mFPSActor;

	class SphereActor*				mSphere;

	class CubeActor*				mCube;

	class DiceActor*				mDice;

	class CapsuleActor*				mCapsule;
	
	std::vector<class PlaneActor*>	mPlanes;
	
	class SpriteComponent*			mCrosshair;
	
	SoundEvent						mMusicEvent;

	class Text*						mTestText;

	//DirectionalLight				mDirLight;
};