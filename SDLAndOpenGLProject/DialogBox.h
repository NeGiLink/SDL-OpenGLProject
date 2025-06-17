#pragma once
#include "Canvas.h"
#include "Image.h"

//�_�C�A���O�{�b�N�XUI�̃N���X
//�قڎ�������Ă��Ȃ��̂�
////���Ќ��̃t�@�C��
class GameDialogBox : public Canvas
{
private:
	Button* mButton01;

	Button* mButton02;
public:
	// (���Ɉ��������͌��ɑΉ����܂�)
	GameDialogBox(const string& text,
		std::function<void()> onOK);
	GameDialogBox(const char8_t* text,
		std::function<void()> onOK);
	~GameDialogBox();
};