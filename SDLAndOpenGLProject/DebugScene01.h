#pragma once
#include "BaseScene.h"

//通常のモデルなどを生成しているゲームシーン
class DebugScene01 : public BaseScene
{
private:
	// Game-specific code
	class FPSActor*					mFPSActor;

	class MeshActor*				mSphere;

	class MeshActor*				mCube;

	class MeshActor*				mDice;

	class MeshActor*				mDamageTrap;

	class MeshActor*				mHealthObject;

	class MeshActor*				mCapsule;

	class MeshActor*				mDebugStage;

	class MeshActor*				mDebugStage2;

	class MeshActor*				mTarget1;
	class MeshActor*				mTarget2;
	class MeshActor*				mTarget3;

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