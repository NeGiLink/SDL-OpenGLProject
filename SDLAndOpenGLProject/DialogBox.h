#pragma once
#include "Canvas.h"
#include "Image.h"

//�_�C�A���O�{�b�N�XUI�̃N���X
//�قڎ�������Ă��Ȃ��̂�
////���Ќ��̃t�@�C��
class GameDialogBox : public Canvas
{
public:
	// (���Ɉ��������͌��ɑΉ����܂�)
	GameDialogBox(const string& text,
		std::function<void()> onOK);
	~GameDialogBox();
};