#include "PauseMenu.h"


PauseMenu::PauseMenu()
	:UIScreen()
{
	GameStateClass::SetGameState(GameState::TimeStop);
	SetRelativeMouseMode(false);
	SetTitle("PauseTitle");
	AddButton("ResumeButton", [this]() {
		Close();
		});
	AddButton("QuitButton", [this]() {
		new GameDialogBox("QuitText",
			[this]() {
				GameStateClass::SetGameState(GameState::GameEnd);
			});
		});
}

PauseMenu::~PauseMenu()
{
	SetRelativeMouseMode(true);
	GameStateClass::SetGameState(GameState::GamePlay);
}

void PauseMenu::HandleKeyPress(int key)
{
	UIScreen::HandleKeyPress(key);

	if (key == SDLK_ESCAPE)
	{
		Close();
	}
}