#pragma once
#include "UIScreen.h"
//�_�C�A���O�{�b�N�XUI�̃N���X
//�قڎ�������Ă��Ȃ��̂�
//�Q�l�R�[�h�Ƃقړ���
class DialogBox : public UIScreen
{
public:
	// (���Ɉ��������͌��ɑΉ����܂�)
	DialogBox(class BaseScene* game, const std::string& text,
		std::function<void()> onOK);
	~DialogBox();
};

