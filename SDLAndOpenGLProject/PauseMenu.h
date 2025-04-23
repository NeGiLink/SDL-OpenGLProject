#pragma once
#include "UIScreen.h"

//ポーズUIのクラス
class PauseMenu : public UIScreen
{
public:
	PauseMenu();
	~PauseMenu();

	void HandleKeyPress(int key) override;
};

