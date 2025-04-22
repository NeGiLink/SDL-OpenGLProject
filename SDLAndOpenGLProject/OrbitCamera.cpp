#include "OrbitCamera.h"
#include "Actor.h"

OrbitCamera::OrbitCamera(ActorObject* owner)
	:CameraComponent(owner)
	, mOffset(-400.0f, 0.0f, 0.0f)
	, mUp(Vector3::UnitZ)
	, mPitchSpeed(0.0f)
	, mYawSpeed(0.0f)
{
}

void OrbitCamera::Update(float deltaTime)
{
	CameraComponent::Update(deltaTime);
	// ���[���h�A�b�v�Ɋւ��郈�[�̂��߂̃N�H�[�^�j�I�����쐬����B
	Quaternion yaw(Vector3::UnitZ, mYawSpeed * deltaTime);
	// �I�t�Z�b�g��ό`���ă��[�ŏ�Ɉړ����܂��B
	mOffset = Vector3::Transform(mOffset, yaw);
	mUp = Vector3::Transform(mUp, yaw);

	// �����̃x�N�g������J�����̑O��/�E���v�Z���܂��B
	// Forward owner.position - (owner.position + offset)
	// = -offset
	Vector3 forward = -1.0f * mOffset;
	forward.Normalize();
	Vector3 right = Vector3::Cross(mUp, forward);
	right.Normalize();

	// �J�����̉E���̃s�b�`�ɑ΂���l�������쐬����
	Quaternion pitch(right, mPitchSpeed * deltaTime);
	// �s�b�`�ŃJ�����̃I�t�Z�b�g�Ə��ϊ�����
	mOffset = Vector3::Transform(mOffset, pitch);
	mUp = Vector3::Transform(mUp, pitch);

	// �ϊ��s����v�Z����
	Vector3 target = mOwner->GetLocalPosition();
	Vector3 cameraPos = target + mOffset;
	Matrix4 view = Matrix4::CreateLookAt(cameraPos, target, mUp);
	SetViewMatrix(view);
}