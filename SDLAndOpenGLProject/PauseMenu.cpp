#include "PauseMenu.h"
#include "WinMain.h"
#include "DialogBox.h"
#include <SDL3/SDL.h>

PauseMenu::PauseMenu(WinMain* game)
	:UIScreen(game)
{
	mGame->SetState(WinMain::EPaused);
	SetRelativeMouseMode(false);
	SetTitle("PauseTitle");
	AddButton("ResumeButton", [this]() {
		Close();
		});
	AddButton("QuitButton", [this]() {
		new DialogBox(mGame, "QuitText",
			[this]() {
				mGame->SetState(WinMain::EQuit);
			});
		});
}

PauseMenu::~PauseMenu()
{
	SetRelativeMouseMode(true);
	mGame->SetState(WinMain::EGameplay);
}

void PauseMenu::HandleKeyPress(int key)
{
	UIScreen::HandleKeyPress(key);

	if (key == SDLK_ESCAPE)
	{
		Close();
	}
}