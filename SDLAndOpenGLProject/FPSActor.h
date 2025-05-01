#pragma once
#include "Actor.h"
#include "SoundEvent.h"

#include "BasicInputAction.h"

#include "AudioSystem.h"
#include "AudioComponent.h"
#include "FPSCamera.h"
#include "MeshRenderer.h"
#include "BallActor.h"
#include "BoxCollider.h"
#include "PlaneActor.h"
#include "DiceActor.h"

//��l�̎��_�̃v���C���[����N���X
//���݃Q�[�����̈ړ��Ɏg�p���Ă��܂��B
class FPSActor : public ActorObject
{
public:
	FPSActor();

	void UpdateActor(float deltaTime) override;
	
	void ActorInput(const struct InputState& keys) override;

	void SetFootstepSurface(float value);

	void SetVisible(bool visible);

	void OnCollisionEnter(class ActorObject* target) override;

	void OnCollisionExit(class ActorObject* target) override;
private:
	BasicInputAction*		mBasicInput;
	
	class AudioComponent*	mAudioComp;
	
	class MeshRenderer*		mMeshComp;
	
	class FPSCamera*		mFPSCamera;
	
	class BoxCollider*		mBoxComp;

	class DiceActor*		mDice;
	
	SoundEvent				mFootstep;
	
	float					mLastFootstep;
};