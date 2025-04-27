#pragma once
#include "CameraComponent.h"
#include "Actor.h"

//��l�̎��_�J�����̃N���X
class FPSCamera : public CameraComponent
{
public:
	FPSCamera(class ActorObject* owner);

	void Update(float deltaTime) override;

	float GetPitch() const { return mPitch; }
	float GetPitchSpeed() const { return mPitchSpeed; }
	float GetMaxPitch() const { return mMaxPitch; }

	void SetPitchSpeed(float speed) { mPitchSpeed = speed; }
	void SetMaxPitch(float pitch) { mMaxPitch = pitch; }
private:
	// �s�b�`�̉�]/�b���x�B
	float mPitchSpeed;
	// �O������̍ő�s�b�`�΍��B
	float mMaxPitch;
	// ���݂̃s�b�`�B
	float mPitch;
};

