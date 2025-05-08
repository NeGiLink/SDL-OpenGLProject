#pragma once
#include "BaseScene.h"
#include "Math.h"
#include "SoundEvent.h"

//スケルタルメッシュなどの人型のキャラクターを生成しているシーン
class DebugScene02 : public BaseScene
{
public:
	DebugScene02(class GameWinMain* winMain);
	
	bool Initialize()override;
	
	bool InputUpdate()override;

	bool Update()override;
	
	void HandleKeyPress(int key)override;
private:
	// Game-specific code

	class TestCharacter*			mTestCharacter;

	class YBotActor*				mYBotActor;

	class SmallCharacter*			mSmallCharacter;
	
	class SpriteComponent*			mCrosshair;
	
	SoundEvent						mMusicEvent;

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

};