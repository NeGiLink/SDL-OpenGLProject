#include "FollowObjectMovement.h"

FollowObjectMovement::FollowObjectMovement(ActorObject* owner, int updateOrder)
	:Component(owner, updateOrder)
	, mMaxSpeed(8.0f)
	, mGravity(false)
	, mJumping(false)
	, mVelocity(Vector3::Zero)
	, mInputDirection(Vector3::Zero)
{
	mGravity = true;
}

void FollowObjectMovement::FixedUpdate(float deltaTime)
{
	//�Ǐ]�I�u�W�F�N�g�̉�]����
	//�ړ������ɐ��ʂ��������鏈��
	float rotationSpeed = 25.0f * deltaTime;
	Quaternion targetRotation;
	if (!Math::NearZero(mVelocity.x)|| !Math::NearZero(mVelocity.y)|| !Math::NearZero(mVelocity.z))
	{
		targetRotation = Quaternion::LookRotation(mVelocity, Vector3::UnitY);
		Quaternion currnetRotation = Quaternion::RotateTowards(mOwner->GetLocalRotation(), targetRotation, rotationSpeed);
		mOwner->SetLocalRotation(currnetRotation);
	}

	//�ړ�����
	// �J�����̕����őO�㍶�E�����߂Ĉړ�
	// �J�����̑O���ƉE�x�N�g�����擾�iXZ���ʂɓ��e�j
	Vector3 camForward = mGame->GetCamera()->GetCameraForward();
	camForward.y = 0;
	camForward.Normalize();
	// �J�����̉E�x�N�g�����擾
	Vector3 camRight = mGame->GetCamera()->GetCameraRight();
	camRight.y = 0;
	camRight.Normalize();

	// ���͕����Ɋ�Â��ړ��x�N�g���iz���O��Ax�����E�j
	Vector3 moveDir = (camForward * mInputDirection.z) + (camRight * mInputDirection.x);

	if (!Math::NearZero(moveDir.LengthSq())) {
		Vector3 pos = mOwner->GetLocalPosition();
		moveDir.Normalize();
		pos += moveDir * mMaxSpeed * deltaTime;
		mOwner->SetLocalPosition(pos);
	}
}

void FollowObjectMovement::Update(float deltaTime)
{
	//�����͂ƃJ������yaw�}�g���b�N�X����ړ��ʂ��擾
	Vector3 inputDir = mInputDirection;
	// �J�����̉�]�s����擾�iyaw�����j
	// Y����]�̂�
	Matrix4 cameraYawRot = mGame->GetCamera()->GetCameraYawRot();
	Vector3 moveDir = Vector3::Transform(inputDir, cameraYawRot);
	if (moveDir.Length() <= 0) { return; }
	mVelocity = moveDir;
}

void FollowObjectMovement::MoveInputUpdate(const InputState& keys)
{
	mInputDirection = Vector3();
	// wasd movement
	if (keys.Keyboard.GetKey(SDL_SCANCODE_W))
	{
		mInputDirection.z = 1.0f;
	}
	if (keys.Keyboard.GetKey(SDL_SCANCODE_S))
	{
		mInputDirection.z = -1.0f;
	}
	if (keys.Keyboard.GetKey(SDL_SCANCODE_A))
	{
		mInputDirection.x = -1.0f;
	}
	if (keys.Keyboard.GetKey(SDL_SCANCODE_D))
	{
		mInputDirection.x = 1.0f;
	}

	if (mGravity)
	{
		if (keys.Keyboard.GetKeyDown(SDL_SCANCODE_SPACE) && !mJumping)
		{
			if (mOwner->GetRigidbody())
			{
				mOwner->GetRigidbody()->AddForce(Vector3::UnitY * 1000.0f);
			}
		}
	}
}
