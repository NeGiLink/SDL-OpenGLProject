#pragma once
#include "UIScreen.h"

//�|�[�YUI�̃N���X
class PauseMenu : public UIScreen
{
public:
	PauseMenu();
	~PauseMenu();

	void HandleKeyPress(int key) override;
};

