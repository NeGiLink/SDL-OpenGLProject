#pragma once
#include "Canvas.h"
#include "DialogBox.h"
#include <SDL3/SDL.h>

//���Ќ��̃t�@�C��
//�|�[�YUI�̃N���X
class PauseMenu : public Canvas
{
public:
			PauseMenu();
			~PauseMenu();

	void	HandleKeyPress(int key) override;
};

