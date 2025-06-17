#pragma once
#include "BaseCamera.h"
#include "Actor.h"

//���Е������ꕔ���������t�@�C��
//��l�̎��_�J�����̃N���X
class FPSCamera : public BaseCamera
{
private:
	float	mAngularSpeed;
	// �s�b�`�̉�]/�b���x�B
	float	mPitchSpeed;
	// �O������̍ő�s�b�`�΍��B
	float	mMaxPitch;

	float	mAngular;
	// ���݂̃s�b�`�B
	float	mPitch;

	//�}�E�X�X�s�[�h
	float	mHorizontalMouseSpeed;
	float	mVertexMouseSpeed;
public:
			FPSCamera(class ActorObject* owner);

	void	Update(float deltaTime) override;

	//��l�̎��_�̃J�����������s���s�b�`���x���擾����֐�
	void	CameraInputUpdate();

	float	GetAngular() const { return mAngular; }
	float	GetAngularSpeed() const { return mAngularSpeed; }
	float	GetPitch() const { return mPitch; }
	float	GetPitchSpeed() const { return mPitchSpeed; }
	float	GetMaxPitch() const { return mMaxPitch; }

	float	GetHorizontalMouseSpeed()const { return mHorizontalMouseSpeed; }
	float	GetVertexMouseSpeed()const { return mVertexMouseSpeed; }

	void	SetAngularSpeed(float speed) { mAngularSpeed = speed; }
	void	SetPitchSpeed(float speed) { mPitchSpeed = speed; }
	void	SetMaxPitch(float pitch) { mMaxPitch = pitch; }

	void	SetHorizontalMouseSpeed(float speed) { mHorizontalMouseSpeed = speed; }
	void	SetVertextMouseSpeed(float speed) { mVertexMouseSpeed = speed; }
};