#include "TitleScene.h"

TitleScene::TitleScene(GameWinMain* winMain)
	:BaseScene(winMain)
{
}

TitleScene::~TitleScene()
{
}

bool TitleScene::Initialize()
{
	BaseScene::Initialize();

	/*
	mDebugStage = new MeshActor();
	mDebugStage->Load("DebugStage.fbx");
	Vector3 pos = Vector3(0.0f, -1.0f, 0.0f);
	mDebugStage->SetLocalPosition(pos);
	mDebugStage->SetActorTag(ActorTag::Ground);
	mDebugStage->AddBoxCollider();
	*/

	mTitleCanvas = new TitleCanvas();

	mFreeCameraActor = new FreeCameraActor();
	mFreeCameraActor->SetLocalPosition(Vector3(0.0f, 0.0f, 0.0f));
	mFreeCameraActor->GetCamera()->SetCameraPosition(mFreeCameraActor->GetPosition(), Vector3::UnitZ);

	return true;
}

bool TitleScene::InputUpdate(const InputState& state)
{
	if (!mCanvasStack.empty())
	{
		mCanvasStack.back()->ProcessInput(state);
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
