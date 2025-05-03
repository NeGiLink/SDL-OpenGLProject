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
	Vector3 ComputeCameraPos() const;

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
};

