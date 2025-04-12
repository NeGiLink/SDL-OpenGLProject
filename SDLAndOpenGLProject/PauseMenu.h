#pragma once
#include "UIScreen.h"

//ポーズUIのクラス
class PauseMenu : public UIScreen
{
public:
	PauseMenu(class BaseScene* game);
	~PauseMenu();

	void HandleKeyPress(int key) override;
};

