#pragma once
#include "UIScreen.h"
#include "DialogBox.h"
#include <SDL3/SDL.h>

//�|�[�YUI�̃N���X
class PauseMenu : public UIScreen
{
public:
	PauseMenu();
	~PauseMenu();

	void HandleKeyPress(int key) override;
};

