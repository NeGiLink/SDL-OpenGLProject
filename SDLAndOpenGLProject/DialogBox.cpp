#include "DialogBox.h"
#include "WinMain.h"
#include "BaseScene.h"
#include "Renderer.h"
#include <SDL3/SDL.h>
#include "Image.h"

DialogBox::DialogBox(BaseScene* game, const std::string& text,
	std::function<void()> onOK)
	:UIScreen(game)
{
	// ダイアログボックスの位置を調整する
	mBGPos = Vector2(0.0f, 0.0f);
	mTitlePos = Vector2(0.0f, 100.0f);
	mNextButtonPos = Vector2(0.0f, 0.0f);

	mBackground = new Image(game, false);
	mBackground->Load("Assets/DialogBG.png");
	SetTitle(text, Vector3::Zero, 30);
	AddButton("OKButton", [onOK]() {
		onOK();
		});
	AddButton("CancelButton", [this]() {
		Close();
		});
}

DialogBox::~DialogBox()
{
}