#include "TitleCanvas.h"

TitleCanvas::TitleCanvas()
	:Canvas()
{
	GameStateClass::SetGameState(GameState::TimeStop);
	SetRelativeMouseMode(false);

	mTitleFont = new Text(mGame->GetFont("NotoSansJP-Bold.ttf"), Vector2::Zero);

	mTitleLogo = new Image();
	mTitleLogo->Load("TitleLogo.png");
	float width = WindowRenderProperty::GetWidth();
	float height = WindowRenderProperty::GetHeight();
	mTitleLogo->SetPosition(Vector2(0,200));

	const char8_t* t8 = u8"�J�n";
	CreateButton("�J�n", Vector2(0.0f, 0.0f), [this]() {
		SceneManager::LoadScene(1);
		});

	CreateButton("�I��", Vector2(0.0f, -80.0f), [this]() {
		new GameDialogBox("�I�����܂����H",
			[this]() {
				GameStateClass::SetGameState(GameState::GameEnd);
			});
		});
}

void TitleCanvas::Update(float deltaTime)
{
	Canvas::Update(deltaTime);
}
