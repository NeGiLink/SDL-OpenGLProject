#pragma once
#include "Canvas.h"
#include "PhysWorld.h"
#include "TargetComponent.h"
#include "Actor.h"

class TPSCanvas : public Canvas
{
protected:

	Image* mSceneNameFrame;
	//フレームレート表示テキスト
	Text* mFrameRateText;

	Text* mPoseButtonText;

	Image* mPoseButtonFrame;

	Image* mPoseButton;

	class Text* mSceneLoadButtonText;

	//***アニメーション再生ボタンテキスト***
	class Text* mSceneNameText;

	Image* mPoseFrame;

	class Text* mTPoseButtonText;

	class Text* mIdlePoseButtonText;

	class Text* mRunPoseButtonText;

	class Text* mJumpPoseButtonText;

	class Text* mCapoeiraPoseButtonText;

	class Image* mHelthBarFrame;

	class Image* mHelthBar;
public:
	// (下に引く順序は後ろに対応します)
	TPSCanvas();

	void									Update(float deltaTime) override;


	Image*									GetHelthBar() { return mHelthBar; }
};

