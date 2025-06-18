#pragma once
#include "BaseScene.h"
#include "SoundEventClip.h"

#include "Stages01.h"

//スケルタルメッシュなどの人型のキャラクターを生成しているシーン
class DebugScene02 : public BaseScene
{
private:
	// Game-specific code

	class TPSPlayer*				mTPSPlayer;

	Stages01*						mStages01;

	class SpriteComponent*			mCrosshair;

	SoundEventClip					mMusicEvent;

	//フレームレート表示テキスト
	class Text*						mFrameRateText;

	class Text*						mPoseButtonText;

	class Text*						mSceneLoadButtonText;

	//***アニメーション再生ボタンテキスト***
	class Text*						mSceneNameText;

	class Text*						mTPoseButtonText;

	class Text*						mIdlePoseButtonText;

	class Text*						mRunPoseButtonText;

	class Text*						mJumpPoseButtonText;

	class Text*						mCapoeiraPoseButtonText;
public:
									DebugScene02(class GameWinMain* winMain);
	
	bool							Initialize()override;
	
	bool							InputUpdate(const InputState& state)override;

	bool							Update()override;
	
	void							HandleKeyPress(int key)override;

};