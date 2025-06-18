#include "DebugScene01.h"
#include "GameFunctions.h"

DebugScene01::DebugScene01(GameWinMain* winMain)
	:BaseScene(winMain)
{
}

bool DebugScene01::Initialize()
{
	BaseScene::Initialize();
	// Load English text
	LoadText("Assets/English.gptext");

	Quaternion q;


	// ポイントライトメッシュをロードする
	//mWinMain->GetRenderer()->SetPointLightMesh(mWinMain->GetRenderer()->GetMesh("PointLight.gpmesh"));

	// 環境光の設定
	mWinMain->GetRenderer()->SetAmbientLight(Vector3(0.4f, 0.4f, 0.4f));
	DirectionalLight& dir = mWinMain->GetRenderer()->GetDirectionalLight();
	dir.mDirection = Vector3(0.0f, -0.707f, -0.707f);
	dir.mDiffuseColor = Vector3(0.78f, 0.88f, 1.0f);
	dir.mSpecColor = Vector3(0.8f, 0.8f, 0.8f);
	
	// ゲーム内のUI生成
	mHUD = new HUD();

	Font* font = GetFont("NotoSansJP-Bold.ttf");
	//シーン名生成
	mSceneNameText = new Text(font, Vector2(500, 350));
	mSceneNameText->SetUTF_8Text(u8"デバッグシーン1");
	mSceneNameText->SetFontSize(40);
	
	mPoseButtonText = new Text(font, Vector2(-600, 350));
	mPoseButtonText->SetUTF_8Text(u8"ESC Key");
	mPoseButtonText->SetFontSize(40);

	mSceneLoadButtonText = new Text(font, Vector2(450, 150));
	mSceneLoadButtonText->SetUTF_8Text(u8"シーンのロード:L Key");
	mSceneLoadButtonText->SetFontSize(48);

	mFrameRateText = new Text(font, Vector2(500, 250));
	float time = Time::gDeltaTime;
	mFrameRateText->SetText(std::to_string(time));
	mFrameRateText->SetFontSize(40);
	
	// BGMスタート
	mMusicEvent = mAudioSystem->PlayEvent("event:/Music3");
	// BGM一時停止
	mMusicEvent.Pause();

	// マウスカーソル位置を固定
	SDL_SetWindowRelativeMouseMode(mWinMain->GetRenderer()->GetWindow(), true);
	// マウスカーソルを非表示
	SDL_GetRelativeMouseState(nullptr, nullptr);

	// デバッグ用のステージ追加
	mStages = new Stages00();
	mStages->Initialize();

	// プレイヤー生成
	mFPSActor = new FPSActor();
	mFPSActor->SetLocalPosition(Vector3(0.0f,1.0f,0.0f));

	mPlayer = mFPSActor;

	mCube = new MeshActor();
	mCube->Load("Cube.fbx");
	mCube->SetLocalPosition(Vector3(0.0f, 0.0f, 6.0f));
	mCube->AddBoxCollider();
	
	mCapsule = new MeshActor();
	mCapsule->Load("Capsule.fbx");
	mCapsule->SetLocalPosition(Vector3(4.0f, 0.5f, 6.0f));
	mCapsule->AddCapsuleCollider();
	mCube->AddChildActor(mCapsule);


	mSphere = new MeshActor();
	mSphere->Load("Sphere.fbx");
	mSphere->SetLocalPosition(Vector3(-4.0f, 0.0f, 6.0f));
	mSphere->AddSphereCollider();
	mSphere->AddChildActor(mCapsule);
	mCube->AddChildActor(mSphere);

	mDice = new MeshActor();
	mDice->Load("TestCube.fbx");
	mDice->SetLocalPosition(Vector3(8.0f, 0.0f, 6.0f));
	mDice->AddBoxCollider();

	mDamageTrap = new MeshActor();
	mDamageTrap->Load("DamageTrap.fbx");
	mDamageTrap->SetLocalPosition(Vector3(-20.0f, 0.7f, -4.0f));
	mDamageTrap->SetActorTag(ActorTag::Enemy);
	mDamageTrap->AddSphereCollider();
	mDamageTrap->SetColliderMode(false);

	mHealthObject = new MeshActor();
	mHealthObject->Load("Health.fbx");
	mHealthObject->SetLocalScale(0.5f);
	mHealthObject->SetLocalPosition(Vector3(-20.0f, 1.0f, 4.0f));
	mHealthObject->SetActorTag(ActorTag::Recovery);
	mHealthObject->AddBoxCollider();
	mHealthObject->SetColliderMode(false);


	return true;
}

bool DebugScene01::InputUpdate(const InputState& state)
{
	BaseScene::InputUpdate(state);
	if (state.Keyboard.GetKeyDown(KEY_O))
	{
		mMusicEvent.Pause();
	}
	else if (state.Keyboard.GetKeyDown(KEY_P))
	{
		mMusicEvent.Restart();
	}
	bool L = state.Keyboard.GetKeyDown(KEY_L);
	if (L)
	{
		SceneManager::LoadScene(2);
	}
	else if (!mUIStack.empty())
	{
		mUIStack.back()->ProcessInput(state);
	}


	return true;
}

bool DebugScene01::Update()
{
	float time = Time::GetFrameRate();
	mFrameRateText->SetText("FPS : " + FloatToString::ToStringWithoutDecimal(time));

	//簡易的なY軸回転処理
	float rotationAmountY = mHealthObject->GetRotationAmountY();
	rotationAmountY += 5 * Time::gDeltaTime;
	mHealthObject->SetRotationAmountY(rotationAmountY);
	Quaternion r = Quaternion(Vector3::UnitY, rotationAmountY);
	mHealthObject->SetLocalRotation(r);

	//簡易的なY軸回転処理
	rotationAmountY = mDamageTrap->GetRotationAmountY();
	rotationAmountY += 5 * Time::gDeltaTime;
	mDamageTrap->SetRotationAmountY(rotationAmountY);
	r = Quaternion(Vector3::UnitY, rotationAmountY);
	mDamageTrap->SetLocalRotation(r);

	BaseScene::Update();
	return true;
}

void DebugScene01::HandleKeyPress(int key)
{
	switch (key)
	{
	case SDLK_ESCAPE:
		mPauseMenu = new PauseMenu();
		break;
	default:
		break;
	}
	BaseScene::HandleKeyPress(key);
}
