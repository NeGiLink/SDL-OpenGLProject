#pragma once
#include "BaseScene.h"
#include "FreeCameraActor.h"
#include "TitleCanvas.h"

class TitleScene : public BaseScene
{
private:
	class FreeCameraActor*			mFreeCameraActor;

	class TitleCanvas*				mTitleCanvas;
public:
									TitleScene(class GameWinMain* winMain);

	bool							Initialize()override;

	bool							InputUpdate(const InputState& state)override;

	bool							Update()override;

	void							HandleKeyPress(int key)override;
};

