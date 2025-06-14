#include "DialogBox.h"

GameDialogBox::GameDialogBox(const string& text,
	std::function<void()> onOK)
	:Canvas()
{

	// �_�C�A���O�{�b�N�X�̈ʒu�𒲐�����
	mBGPos = Vector2(0.0f, 0.0f);
	mTitlePos = Vector2(0.0f, 100.0f);
	mNextButtonPos = Vector2(0.0f, 0.0f);

	mBackground = new Image();
	mBackground->Load("DialogBG.png");

	mTitleFont = new Text(mGame->GetFont("NotoSansJP-Bold.ttf"), Vector2::Zero);
	mTitleFont->SetPosition(mTitlePos);
	SetTitle(text, Vector3::Zero, 30);
	CreateButton("�͂�",Vector2(0.0f,0.0f), [onOK]() {
		onOK();
		});
	CreateButton("������",Vector2(0.0f, -80.0f), [this]() {
		Close();
		});
}

GameDialogBox::~GameDialogBox()
{
	mBackground->SetState(Image::EDestroy);
}