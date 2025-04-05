#pragma once
#include "UIScreen.h"

class FrameRate : public UIScreen
{
public:
	FrameRate(class BaseScene* game, const std::string& text,
		std::function<void()> onOK);
	~FrameRate();
};

