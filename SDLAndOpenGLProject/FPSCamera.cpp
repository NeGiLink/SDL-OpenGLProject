#include "FPSCamera.h"

FPSCamera::FPSCamera(ActorObject* owner)
	:BaseCamera(owner)
	, mAngularSpeed(0.0f)
	, mPitchSpeed(0.0f)
	, mMaxPitch(Math::Pi / 3.0f)
	, mPitch(0.0f)
	, mHorizontalMouseSpeed(500.0f)
	, mVertexMouseSpeed(500.0f)
{
}

void FPSCamera::Update(float deltaTime)
{
	// �e�X�V���Ăяo���B�i���͉������Ȃ��j
	BaseCamera::Update(deltaTime);

	//���_��]
	if (!Math::NearZero(mAngularSpeed))
	{
		Quaternion rot = mOwner->GetLocalRotation();
		float angle = mAngularSpeed * deltaTime;
		// Create quaternion for incremental rotation
		// (Rotate about up axis)
		Quaternion inc(Vector3::UnitY, angle);
		// Concatenate old and new quaternion
		rot = Quaternion::Concatenate(rot, inc);
		mOwner->SetRotation(rot);
	}

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

void FPSCamera::CameraInputUpdate()
{
	//SDL�Ń}�E�X�̈ړ����l���擾
	float x, y;
	SDL_GetRelativeMouseState(&x, &y);
	//�}�E�X�ł̍ő�ړ����l��ݒ�

	// �ő呬�x�ł̉�]/�b
	const float maxAngularSpeed = Math::Pi * 8;
	float angularSpeed = 0.0f;
	if (x != 0)
	{
		// [-1.0, 1.0]�ɕϊ�����
		angularSpeed = static_cast<float>(x) / mHorizontalMouseSpeed;
		// ��]/�b�Ŋ|����
		angularSpeed *= maxAngularSpeed;
	}
	mAngularSpeed = angularSpeed;

	// �������v�Z����
	const float maxPitchSpeed = Math::Pi * 8;
	float pitchSpeed = 0.0f;
	if (y != 0)
	{
		// [-1.0, 1.0]�ɕϊ�����
		pitchSpeed = static_cast<float>(y) / mVertexMouseSpeed;
		pitchSpeed *= maxPitchSpeed;
	}
	mPitchSpeed = pitchSpeed;
}
