#pragma once
#include "Actor.h"
#include "SoundEvent.h"
#include "MoveComponent.h"
#include "AudioSystem.h"
#include "AudioComponent.h"
#include "FPSCamera.h"
#include "MeshRenderer.h"
#include "BallActor.h"
#include "BoxCollider.h"
#include "PlaneActor.h"

//一人称視点のプレイヤー操作クラス
//現在ゲーム内の移動に使用しています。
class FPSActor : public ActorObject
{
public:
	FPSActor();

	void UpdateActor(float deltaTime) override;
	
	void ActorInput(const struct InputState& keys) override;

	void Shoot();

	void SetFootstepSurface(float value);

	void SetVisible(bool visible);

	void FixCollisions();

	void OnCollisionEnter(class ActorObject* target) override;
private:
	class MoveComponent*	mMoveComp;
	
	class AudioComponent*	mAudioComp;
	
	class MeshRenderer*		mMeshComp;
	
	class FPSCamera*		mCameraComp;
	
	class BoxCollider*		mBoxComp;
	
	SoundEvent				mFootstep;
	
	float					mLastFootstep;
};