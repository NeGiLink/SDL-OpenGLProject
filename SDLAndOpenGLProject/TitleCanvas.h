#pragma once
#include "Canvas.h"
#include "DialogBox.h"

class TitleCanvas : public Canvas
{
protected:
	class Image*							mTitleLogo;
public:
											TitleCanvas();

	void									Update(float deltaTime) override;
};

