#include "TitleScene.h"

TitleScene::TitleScene(GameWinMain* winMain)
	:BaseScene(winMain)
{
}

bool TitleScene::Initialize()
{
	BaseScene::Initialize();
	// Load English text
	LoadText("Assets/English.gptext");

	// ポイントライトメッシュをロードする
	mWinMain->GetRenderer()->SetPointLightMesh(mWinMain->GetRenderer()->GetMesh("PointLight.gpmesh"));

	// 環境光の設定
	mWinMain->GetRenderer()->SetAmbientLight(Vector3(0.4f, 0.4f, 0.4f));
	DirectionalLight& dir = mWinMain->GetRenderer()->GetDirectionalLight();
	dir.mDirection = Vector3(0.0f, -0.707f, -0.707f);
	dir.mDiffuseColor = Vector3(0.78f, 0.88f, 1.0f);
	dir.mSpecColor = Vector3(0.8f, 0.8f, 0.8f);

	mTitleCanvas = new TitleCanvas();

	Font* font = GetFont("NotoSansJP-Bold.ttf");

	mFreeCameraActor = new FreeCameraActor();
	mFreeCameraActor->SetLocalPosition(Vector3(0.0f, 0.0f, 0.0f));
	mFreeCameraActor->GetCamera()->SetCameraPosition(mFreeCameraActor->GetPosition(), Vector3::UnitZ);

	return true;
}

bool TitleScene::InputUpdate(const InputState& state)
{
	if (!mUIStack.empty())
	{
		mUIStack.back()->ProcessInput(state);
	}
	BaseScene::InputUpdate(state);
	return true;
}

bool TitleScene::Update()
{
	BaseScene::Update();
	return true;
}

void TitleScene::HandleKeyPress(int key)
{
	BaseScene::HandleKeyPress(key);
}
