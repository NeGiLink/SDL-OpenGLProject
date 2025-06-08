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


	// �|�C���g���C�g���b�V�������[�h����
	mWinMain->GetRenderer()->SetPointLightMesh(mWinMain->GetRenderer()->GetMesh("PointLight.gpmesh"));

	// �����̐ݒ�
	mWinMain->GetRenderer()->SetAmbientLight(Vector3(0.4f, 0.4f, 0.4f));
	DirectionalLight& dir = mWinMain->GetRenderer()->GetDirectionalLight();
	dir.mDirection = Vector3(0.0f, -0.707f, -0.707f);
	dir.mDiffuseColor = Vector3(0.78f, 0.88f, 1.0f);
	dir.mSpecColor = Vector3(0.8f, 0.8f, 0.8f);
	
	// �Q�[������UI����
	mHUD = new HUD();

	Font* font = GetFont("NotoSansJP-Bold.ttf");
	//�V�[��������
	mSceneNameText = new Text(font, Vector2(500, 350));
	mSceneNameText->SetText(u8"�f�o�b�O�V�[��1");
	mSceneNameText->SetFontSize(40);
	
	mPoseButtonText = new Text(font, Vector2(-500, 350));
	mPoseButtonText->SetText(u8"�|�[�Y:ESC Key");
	mPoseButtonText->SetFontSize(40);

	mSceneLoadButtonText = new Text(font, Vector2(450, 150));
	string t = u8"�V�[���̃��[�h:L Key";
	mSceneLoadButtonText->SetText(t);
	mSceneLoadButtonText->SetFontSize(48);

	mFrameRateText = new Text(font, Vector2(500, 250));
	float time = Time::gDeltaTime;
	mFrameRateText->SetText(std::to_string(time));
	mFrameRateText->SetFontSize(40);
	
	// BGM�X�^�[�g
	mMusicEvent = mAudioSystem->PlayEvent("event:/Music3");
	// BGM�ꎞ��~
	mMusicEvent.Pause();

	// �}�E�X�J�[�\���ʒu���Œ�
	SDL_SetWindowRelativeMouseMode(mWinMain->GetRenderer()->GetWindow(), true);
	// �}�E�X�J�[�\�����\��
	SDL_GetRelativeMouseState(nullptr, nullptr);

	// �f�o�b�O�p�̃X�e�[�W�ǉ�
	mDebugStage = new MeshActor();
	mDebugStage->Load("DebugStage.fbx");

	Vector3 pos = Vector3(0.0f, -1.0f, 0.0f);
	mDebugStage->SetLocalPosition(pos);
	mDebugStage->SetActorTag(ActorTag::Ground);
	mDebugStage2 = new MeshActor();
	mDebugStage2->Load("DebugStage.fbx");

	pos = Vector3(0.0f, 9.5f, 10.5f);
	mDebugStage2->SetLocalPosition(pos);
	q = Quaternion(Vector3::UnitX, -Math::PiOver2);
	mDebugStage2->SetLocalRotation(q);

	mDebugStage3 = new MeshActor();
	mDebugStage3->Load("DebugStage.fbx");

	pos = Vector3(0.0f, 9.5f, -10.5f);
	mDebugStage3->SetLocalPosition(pos);
	q = Quaternion(Vector3::UnitX, Math::PiOver2);
	mDebugStage3->SetLocalRotation(q);

	mDebugStage4 = new MeshActor();
	mDebugStage4->Load("DebugStage.fbx");

	pos = Vector3(10.5f, 9.5f, 0.0f);
	mDebugStage4->SetLocalPosition(pos);
	q = Quaternion(Vector3::UnitX, -Math::PiOver2);
	q = Quaternion::Concatenate(q, Quaternion(Vector3::UnitY, -Math::PiOver2));
	mDebugStage4->SetLocalRotation(q);

	// �v���C���[����
	mFPSActor = new FPSActor();
	mFPSActor->SetLocalPosition(Vector3(0.0f,1.0f,0.0f));

	mPlayer = mFPSActor;

	mCube = new MeshActor();
	mCube->Load("Cube.fbx");
	mCube->SetLocalPosition(Vector3(0.0f, 0.5f, 4.0f));
	/*
	
	mCapsule = new MeshActor();
	mCapsule->Load("Capsule.fbx");
	mCapsule->SetLocalPosition(Vector3(2.0f, 2.0f, 4.0f));
	mCube->AddChildActor(mCapsule);


	mSphere = new MeshActor();
	mSphere->Load("Sphere.fbx");
	mSphere->SetLocalPosition(Vector3(-2.0f, 0.5f, 4.0f));
	mCube->AddChildActor(mSphere);

	mDice = new MeshActor();
	mDice->Load("TestCube.fbx");
	mDice->SetLocalPosition(Vector3(4.0f, 0.5f, 4.0f));

	mDamageTrap = new MeshActor();
	mDamageTrap->Load("DamageTrap.fbx");
	mDamageTrap->SetLocalPosition(Vector3(0.0f, 0.7f, -4.0f));
	mDamageTrap->SetActorTag(ActorTag::Enemy);
	mDamageTrap->SetTrigger(false);

	mHealthObject = new MeshActor();
	mHealthObject->Load("Health.fbx");
	mHealthObject->SetLocalScale(0.5f);
	mHealthObject->SetLocalPosition(Vector3(4.0f, 1.0f, -4.0f));
	mHealthObject->SetActorTag(ActorTag::Recovery);
	mHealthObject->SetTrigger(false);

	// �I�I�u�W�F�N�g����
	q = Quaternion();
	mTarget1 = new MeshActor();
	mTarget1->Load("Target.fbx");
	mTarget1->SetLocalPosition(Vector3(0.0f, 2.0f, 10.0f));
	mTarget1->SetLocalRotation(q);
	new TargetComponent(mTarget1);
	mTarget2 = new MeshActor();
	mTarget2->Load("Target.fbx");
	mTarget2->SetLocalPosition(Vector3(-5.0f, 2.0f, 10.0f));
	mTarget2->SetLocalRotation(q);
	new TargetComponent(mTarget2);
	mTarget3 = new MeshActor();
	mTarget3->Load("Target.fbx");
	mTarget3->SetLocalPosition(Vector3(5.0f, 2.0f, 10.0f));
	mTarget3->SetLocalRotation(q);
	new TargetComponent(mTarget3);
	*/


	return true;
}

bool DebugScene01::InputUpdate()
{
	//���͑���
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			//���s���I�������true
		case SDL_EVENT_QUIT:
			GameStateClass::SetGameState(GameState::GameEnd);
			break;
			// This fires when a key's initially pressed
			//�L�[�{�[�h�̃{�^�����ǂꂩ��������true
		case SDL_EVENT_KEY_DOWN:
			if (!event.key.repeat)
			{
				if (GameStateClass::mGameState == GameState::GamePlay)
				{
					HandleKeyPress(event.key.key);
				}
				else if (!mUIStack.empty())
				{
					mUIStack.back()->
						HandleKeyPress(event.key.key);
				}
			}
			break;
			//�}�E�X�{�^���̂ǂꂩ��������true
		case SDL_EVENT_MOUSE_BUTTON_DOWN:
			if (!mUIStack.empty())
			{
				mUIStack.back()->
					HandleKeyPress(event.button.button);
			}
		default:
			break;
		}
	}
	const InputState& state = InputSystem::GetState();

	if (GameStateClass::mGameState == GameState::GamePlay)
	{
		for (auto actor : mActors)
		{
			if (actor->GetState() == ActorObject::EActive)
			{
				actor->ProcessInput(state);
			}
		}
	}

	if (state.Keyboard.GetKeyDown(KEY_O))
	{
		mMusicEvent.Pause();
	}
	else if (state.Keyboard.GetKeyDown(KEY_P))
	{
		mMusicEvent.Restart();
	}

	if (state.Keyboard.GetKeyDown(SDL_SCANCODE_L))
	{
		SceneManager::LoadScene(1);
	}
	else if (!mUIStack.empty())
	{
		mUIStack.back()->ProcessInput(state);
	}
	BaseScene::InputUpdate();
	return true;
}

bool DebugScene01::Update()
{
	float time = Time::GetFrameRate();
	mFrameRateText->SetText("FPS : " + FloatToString::ToStringWithoutDecimal(time));

	/*
	//�ȈՓI��Y����]����
	float rotationAmountY = mHealthObject->GetRotationAmountY();
	rotationAmountY += 5 * Time::gDeltaTime;
	mHealthObject->SetRotationAmountY(rotationAmountY);
	Quaternion r = Quaternion(Vector3::UnitY, rotationAmountY);
	mHealthObject->SetLocalRotation(r);

	//�ȈՓI��Y����]����
	rotationAmountY = mDamageTrap->GetRotationAmountY();
	rotationAmountY += 5 * Time::gDeltaTime;
	mDamageTrap->SetRotationAmountY(rotationAmountY);
	r = Quaternion(Vector3::UnitY, rotationAmountY);
	mDamageTrap->SetLocalRotation(r);
	*/

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
