#pragma once
#include "UIScreen.h"

//�|�[�YUI�̃N���X
class PauseMenu : public UIScreen
{
public:
	PauseMenu(class BaseScene* game);
	~PauseMenu();

	void HandleKeyPress(int key) override;
};

