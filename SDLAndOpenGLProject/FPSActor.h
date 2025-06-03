#pragma once
#include "Actor.h"
#include "SoundEventClip.h"
#include "BasicInputAction.h"
#include "AudioSystem.h"
#include "AudioComponent.h"
#include "FPSCamera.h"
#include "MeshRenderer.h"
#include "BallActor.h"
#include "BoxCollider.h"
#include "PlaneActor.h"

//��l�̎��_�̃v���C���[����N���X
//���݃Q�[�����̈ړ��Ɏg�p���Ă��܂��B
class FPSActor : public ActorObject
{
private:
	//���̓N���X
	class BasicInputAction*	mBasicInput;
	//�v���C���[�p�̃T�E���h
	class AudioComponent*	mAudioComp;
	//Mesh
	class MeshRenderer*		mMeshComp;
	//��l�̃J����
	class FPSCamera*		mFPSCamera;
	//�R���C�_�[
	class BoxCollider*		mBoxCollider;
	//����SE
	SoundEventClip			mFootstep;
	//�����̊Ԋu
	float					mLastFootstep;
	//�����̃C�x���g���Ăяo���R�[���o�b�N�ϐ�
	Event<void()>			mEvent;
	//�ȈՓI�ȍő�HP�̕ϐ�
	float					mMaxHP;
	//�ȈՓI��HP�̕ϐ�
	float					mHP;
public:
							FPSActor();

	void					FixedUpdateActor(float deltaTime)override;

	void					UpdateActor(float deltaTime) override;
	
	void					ActorInput(const struct InputState& keys) override;

	void					SetFootstepSurface(float value);

	void					SetVisible(bool visible);

	void					OnCollisionEnter(class ActorObject* target) override;

	void					OnCollisionExit(class ActorObject* target) override;
};