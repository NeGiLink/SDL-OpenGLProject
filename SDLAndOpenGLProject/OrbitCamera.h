#pragma once
#include "CameraComponent.h"

//�O���J�����̃N���X
class OrbitCamera : public CameraComponent
{
public:
	OrbitCamera(class ActorObject* owner);

	void Update(float deltaTime) override;

	float GetPitchSpeed() const { return mPitchSpeed; }
	float GetYawSpeed() const { return mYawSpeed; }

	void SetPitchSpeed(float speed) { mPitchSpeed = speed; }
	void SetYawSpeed(float speed) { mYawSpeed = speed; }
private:
	// �^�[�Q�b�g�̃I�t�Z�b�g�B
	Vector3 mOffset;
	// �J�����̏�����x�N�g���B
	Vector3 mUp;
	// �s�b�`�̉�]/�b���x�B
	float mPitchSpeed;
	// ���[�̉�]/�b���x�B
	float mYawSpeed;
};

