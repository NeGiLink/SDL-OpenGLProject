#include "PauseMenu.h"


PauseMenu::PauseMenu()
	:Canvas()
{
	GameStateClass::SetGameState(GameState::TimeStop);
	SetRelativeMouseMode(false);

	mTitleFont = new Text(mGame->GetFont("NotoSansJP-Bold.ttf"), Vector2::Zero);
	mTitlePos = Vector2(-400.0f, 200.0f);
	mTitleFont->SetPosition(mTitlePos);
	SetTitle("�|�[�Y��");

	CreateButton("�ĊJ",Vector2(-400.0f,100.0f), [this]() {
		Close();
		});

	CreateButton("1�O�ɖ߂�", Vector2(-400.0f, 20.0f), [this]() {
		int s = SceneManager::GetNowSceneIndex() == 1 ? 0 : 1;
		SceneManager::LoadScene(s);
		});

	CreateButton("�I��", Vector2(-400.0f, -60.0f), [this]() {
		new GameDialogBox("�I�����܂����H",
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