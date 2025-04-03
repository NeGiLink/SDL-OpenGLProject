#pragma once
#include "UIScreen.h"

class PauseMenu : public UIScreen
{
public:
	PauseMenu(class BaseScene* game);
	~PauseMenu();

	void HandleKeyPress(int key) override;
};

