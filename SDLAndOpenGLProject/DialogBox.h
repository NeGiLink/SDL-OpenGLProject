#pragma once
#include "Canvas.h"
#include "Image.h"

/*
* ===�G���W����������/Engine internal processing===
*/

//�_�C�A���O�{�b�N�XUI�̃N���X
//��ɃQ�[�����̌�����m�肷�邩�̏����Ɏg������
//�������s���Ďg�p����`�ōl���Ă���B
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