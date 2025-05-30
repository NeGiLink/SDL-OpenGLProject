#pragma once
#include "BaseScene.h"

//通常のモデルなどを生成しているゲームシーン
class DebugScene01 : public BaseScene
{
private:
	// Game-specific code
	class FPSActor*					mFPSActor;

	class SphereActor*				mSphere;

	class CubeActor*				mCube;

	class DiceActor*				mDice;

	class DamageTrap*				mDamageTrap;

	class HealthObject*				mHealthObject;

	class CapsuleActor*				mCapsule;

	class DebugStageActor*			mDebugStage;

	vector<class PlaneActor*>		mPlanes;

	class SpriteComponent*			mCrosshair;

	class SoundEventClip			mMusicEvent;

	class Text*						mSceneNameText;

	class Text*						mPoseButtonText;

	class Text*						mSceneLoadButtonText;

	class Text*						mFrameRateText;

	class PauseMenu*				mPauseMenu;
public:
									DebugScene01(class GameWinMain* winMain);

	bool							Initialize()override;

	bool							InputUpdate()override;

	bool							Update()override;

	void							HandleKeyPress(int key)override;
	class							FPSActor* GetFPSPlayer() { return mFPSActor; }
};