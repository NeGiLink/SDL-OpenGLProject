#include "FollowCamera.h"
#include "Actor.h"

FollowCamera::FollowCamera(ActorObject* owner)
	:CameraComponent(owner)
	, mHorzDist(350.0f)
	, mVertDist(150.0f)
	, mTargetDist(100.0f)
	, mSpringConstant(64.0f)
{
}

void FollowCamera::Update(float deltaTime)
{
	CameraComponent::Update(deltaTime);
	// �΂˒萔���猸�����v�Z����
	float dampening = 2.0f * Math::Sqrt(mSpringConstant);
	// ���z�I�Ȉʒu���v�Z����
	Vector3 idealPos = ComputeCameraPos();
	// ���ۂƗ��z�̈Ⴂ���v�Z����
	Vector3 diff = mActualPos - idealPos;
	// �΂˂̉����x���v�Z����
	Vector3 acel = -mSpringConstant * diff -
		dampening * mVelocity;
	// �X�V���x
	mVelocity += acel * deltaTime;
	// ���ۂ̃J�����ʒu���X�V����
	mActualPos += mVelocity * deltaTime;
	// �^�[�Q�b�g�͏��L�҃A�N�^�[�̑O���ɂ���^�[�Q�b�g����
	Vector3 target = mOwner->GetPosition() +
		mOwner->GetForward() * mTargetDist;
	// ���z�ł͂Ȃ��A�����Ɏ��ۂ̈ʒu���g�p���Ă��������B
	Matrix4 view = Matrix4::CreateLookAt(mActualPos, target,
		Vector3::UnitZ);
	SetViewMatrix(view);
}

void FollowCamera::SnapToIdeal()
{
	// ���ۂ̈ʒu�𗝑z�ɐݒ肷��
	mActualPos = ComputeCameraPos();
	// �[�����x
	mVelocity = Vector3::Zero;
	// �^�[�Q�b�g���v�Z���ĕ\��
	Vector3 target = mOwner->GetPosition() +
		mOwner->GetForward() * mTargetDist;
	// ���z�ł͂Ȃ��A�����Ɏ��ۂ̈ʒu���g�p���Ă��������B
	Matrix4 view = Matrix4::CreateLookAt(mActualPos, target,
		Vector3::UnitZ);
	SetViewMatrix(view);
}

Vector3 FollowCamera::ComputeCameraPos() const
{
	// Actor�̌��Ə�ɃJ�����̈ʒu��ݒ肷��
	Vector3 cameraPos = mOwner->GetPosition();
	cameraPos -= mOwner->GetForward() * mHorzDist;
	cameraPos += Vector3::UnitZ * mVertDist;
	return cameraPos;
}