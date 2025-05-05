#include "FPSActor.h"


FPSActor::FPSActor()
	:ActorObject()
{
	mBasicInput = new BasicInputAction(this);

	mRigidbody = new Rigidbody(this);

	mAudioComp = new AudioComponent(this);
	mLastFootstep = 0.0f;
	mFootstep = mAudioComp->PlayEvent("event:/Footstep");
	mFootstep.SetPaused(true);

	mFPSCamera = new FPSCamera(this);

	// ボックスの当たり判定の機能を追加
	mBoxComp = new BoxCollider(this);
	AABB myBox(Vector3(-0.5f, -1.0f, -0.5f),Vector3(0.5f, 0.5f, 0.5f));
	mBoxComp->SetObjectBox(myBox);
	mBoxComp->SetShouldRotate(false);
	mBoxComp->SetStaticObject(false);
	/*
	mDice = new DiceActor();
	AddChildActor(mDice);
	mDice->SetPosition(Vector3(1.5f, 0.0f, 2.0f));
	*/
}

void FPSActor::FixedUpdateActor(float deltaTime)
{

}

void FPSActor::UpdateActor(float deltaTime)
{
	ActorObject::UpdateActor(deltaTime);
	if (!mBasicInput->GetJumping()) 
	{
		// 足音のSEを再生する処理
		mLastFootstep -= deltaTime;
		if ((!Math::NearZero(mBasicInput->GetForwardSpeed()) ||
			!Math::NearZero(mBasicInput->GetStrafeSpeed())) &&
			mLastFootstep <= 0.0f)
		{
			mFootstep.SetPaused(false);
			mFootstep.Restart();
			mLastFootstep = 0.5f;
		}
	}
}

void FPSActor::ActorInput(const struct InputState& keys)
{
	/*
	if (keys.Keyboard.GetKeyDown(SDL_SCANCODE_0))
	{
		RemoveChildActor(mDice);
	}
	else if (keys.Keyboard.GetKeyDown(SDL_SCANCODE_1))
	{
		AddChildActor(mDice);
		mDice->SetPosition(Vector3(1.5f, 0.0f, 2.0f));
	}
	*/


	mBasicInput->MoveInputUpdate(keys);
	mFPSCamera->CameraInputUpdate();
}

void FPSActor::SetFootstepSurface(float value)
{
	//ここで一時停止します。
	// FMODでパラメーターを設定した方法を変更すると、足音が再生されるため
	mFootstep.SetPaused(true);
	mFootstep.SetParameter("Surface", value);
}

void FPSActor::SetVisible(bool visible)
{
	mMeshComp->SetVisible(visible);
}
void FPSActor::OnCollisionEnter(ActorObject* target)
{
	if (target->GetActorTag() != ActorTag::Ground) { return; }
	mBasicInput->SetJumping(false);
	SDL_Log("Ground Hit");
}

void FPSActor::OnCollisionExit(ActorObject* target)
{
	if (target->GetActorTag() != ActorTag::Ground) { return; }
	mBasicInput->SetJumping(true);
	SDL_Log("Jump");
}
