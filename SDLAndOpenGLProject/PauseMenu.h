#pragma once
#include "Canvas.h"
#include "DialogBox.h"
#include <SDL3/SDL.h>

//���Ќ��̃t�@�C��
//�|�[�YUI�̃N���X
class PauseMenu : public Canvas
{
private:
	//class GameDialogBox* mDialogBox;
public:
			PauseMenu();
			~PauseMenu();

	void	HandleKeyPress(int key) override;
};