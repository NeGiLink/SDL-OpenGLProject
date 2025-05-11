#pragma once
#include "BaseCamera.h"
#include "Actor.h"

//�O�l�̎��_�J�����̃N���X
class FollowCamera : public BaseCamera
{
public:
	FollowCamera(class ActorObject* owner);

	void Update(float deltaTime) override;

	void SnapToIdeal();

	void SetHorzDist(float dist) { mHorzDist = dist; }
	void SetVertDist(float dist) { mVertDist = dist; }
	void SetTargetDist(float dist) { mTargetDist = dist; }
	void SetSpringConstant(float spring) { mSpringConstant = spring; }
private:
	//�^�[�Q�b�g�̐^������̏���
	Vector3 ComputeCameraPos() const;
	//�}�E�X�ő���J�����̌������X�V�ł��鏈��
	Vector3 ComputeFreeCameraPos();

	// �J�����̈ʒu
	Vector3		mActualPos;
	// ���ۂ̃J�����̑��x
	Vector3		mVelocity;
	// �����Ǐ]����
	float		mHorzDist;
	// �����t�H���[����
	float		mVertDist;
	// �ڕW�Ƃ̋���
	float		mTargetDist;
	// �΂˒萔�i�����قǍd���j
	float		mSpringConstant;

	// �s�b�`�̉�]/�b���x�B
	float		mPitchSpeed;

	float		mYaw = 0.0f;
	float		mPitch = 0.0f;

	//�}�E�X�X�s�[�h
	float		mHorizontalMouseSpeed;
	float		mVertexMouseSpeed;
	//�J�������Œ肷�邩�̃t���O
	bool		mFixed;
};

