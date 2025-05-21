#include "PauseMenu.h"


PauseMenu::PauseMenu()
	:Canvas()
{
	GameStateClass::SetGameState(GameState::TimeStop);
	SetRelativeMouseMode(false);

	mTitleFont = new Text(mGame->GetFont("Assets/Fonts/Carlito-Regular.ttf"), Vector2::Zero);
	mTitleFont->SetPosition(mTitlePos);
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
	Canvas::HandleKeyPress(key);

	if (key == SDLK_ESCAPE)
	{
		Close();
	}
}