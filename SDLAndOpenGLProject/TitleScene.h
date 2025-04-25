#pragma once
#include "BaseScene.h"

class TitleScene : public BaseScene
{
public:
	TitleScene(class GameWinMain* winMain);

	bool Initialize();

	bool InputUpdate();

	bool Update();

	void HandleKeyPress(int key);
	class FPSActor* GetFPSPlayer() { return mFPSActor; }
private:
	// Game-specific code
	class FPSActor* mFPSActor;

	class SphereActor* mSphere;

	class CubeActor* mCube;

	class DiceActor* mDice;

	class CapsuleActor* mCapsule;

	std::vector<class PlaneActor*>	mPlanes;

	class SpriteComponent* mCrosshair;

	//SoundEvent						mMusicEvent;

	class Text* mTestText;
};