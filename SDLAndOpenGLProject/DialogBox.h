#pragma once
#include "UIScreen.h"
#include "Image.h"

//�_�C�A���O�{�b�N�XUI�̃N���X
//�قڎ�������Ă��Ȃ��̂�
//�Q�l�R�[�h�Ƃقړ���
class GameDialogBox : public UIScreen
{
public:
	// (���Ɉ��������͌��ɑΉ����܂�)
	GameDialogBox(const string& text,
		std::function<void()> onOK);
	~GameDialogBox();
};