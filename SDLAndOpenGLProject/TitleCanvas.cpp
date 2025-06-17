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

	CreateButton(u8"�J�n", Vector2(0.0f, 0.0f), [this]() {
		SceneManager::LoadScene(1);
		});

	CreateButton(u8"�I��", Vector2(0.0f, -80.0f), [this]() {
		//mDialogBox->SetState(Canvas::EActive);
		new GameDialogBox(u8"�I�����܂����H", [this]() {GameStateClass::SetGameState(GameState::GameEnd); });
		});
}

void TitleCanvas::Update(float deltaTime)
{
	Canvas::Update(deltaTime);
}
