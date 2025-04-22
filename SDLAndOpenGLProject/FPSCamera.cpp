#include "FPSCamera.h"
#include "Actor.h"

FPSCamera::FPSCamera(ActorObject* owner)
	:CameraComponent(owner)
	, mPitchSpeed(0.0f)
	, mMaxPitch(Math::Pi / 3.0f)
	, mPitch(0.0f)
{
}

void FPSCamera::Update(float deltaTime)
{
	// �e�X�V���Ăяo���B�i���͉������Ȃ��j
	CameraComponent::Update(deltaTime);
	// �J�����̈ʒu�̓I�[�i�[�̈ʒu�ł��B
	Vector3 cameraPos = mOwner->GetLocalPosition();

	// �s�b�`���x�Ɋ�Â��ăs�b�`���X�V����B
	mPitch += mPitchSpeed * deltaTime;
	// �N�����v�s�b�`��[-max, +max]�ɐ�������B
	mPitch = Math::Clamp(mPitch, -mMaxPitch, mMaxPitch);
	// �I�[�i�[�̉E�x�N�g�������Ƃ���s�b�`��]��\���l�������쐬���܂��B
	Quaternion q(mOwner->GetRight(), mPitch);

	// ���L�҂��s�b�`�N�H�[�^�j�I���őO���ɉ�]������B
	Vector3 viewForward = Vector3::Transform(
		mOwner->GetForward(), q);
	// �����̑O��100���j�b�g�̃^�[�Q�b�g�ʒu�B
	Vector3 target = cameraPos + viewForward * 100.0f;
	// �s�b�`�N�H�[�^�j�I������]�B
	Vector3 up = Vector3::Transform(Vector3::UnitY, q);

	// �}�g���b�N�X���쐬���A�r���[�Ƃ��Đݒ肵�܂��B
	Matrix4 view = Matrix4::CreateLookAt(cameraPos, target, up);
	SetViewMatrix(view);
}