#include "PauseMenu.h"
#include "WinMain.h"
#include "BaseScene.h"
#include "DialogBox.h"
#include <SDL3/SDL.h>

PauseMenu::PauseMenu(BaseScene* game)
	:UIScreen(game)
{
	GameStateClass::SetGameState(GameState::EPaused);
	SetRelativeMouseMode(false);
	SetTitle("PauseTitle");
	AddButton("ResumeButton", [this]() {
		Close();
		});
	AddButton("QuitButton", [this]() {
		new DialogBox(mGame, "QuitText",
			[this]() {
				GameStateClass::SetGameState(GameState::EQuit);
			});
		});
}

PauseMenu::~PauseMenu()
{
	SetRelativeMouseMode(true);
	GameStateClass::SetGameState(GameState::EGameplay);
}

void PauseMenu::HandleKeyPress(int key)
{
	UIScreen::HandleKeyPress(key);

	if (key == SDLK_ESCAPE)
	{
		Close();
	}
}