#include "DialogBox.h"

GameDialogBox::GameDialogBox(const string& text,
	std::function<void()> onOK)
	:UIScreen()
{
	// ダイアログボックスの位置を調整する
	mBGPos = Vector2(0.0f, 0.0f);
	mTitlePos = Vector2(0.0f, 100.0f);
	mNextButtonPos = Vector2(0.0f, 0.0f);

	mBackground = new Image(false);
	mBackground->Load("Assets/DialogBG.png");
	SetTitle(text, Vector3::Zero, 30);
	AddButton("OKButton", [onOK]() {
		onOK();
		});
	AddButton("CancelButton", [this]() {
		Close();
		});
}

GameDialogBox::~GameDialogBox()
{
}