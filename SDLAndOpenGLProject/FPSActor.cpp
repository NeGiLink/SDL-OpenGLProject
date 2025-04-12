#include "FPSActor.h"
#include "MoveComponent.h"
#include <SDL3/SDL_scancode.h>
#include "Renderer.h"
#include "AudioSystem.h"
#include "WinMain.h"
#include "BaseScene.h"
#include "AudioComponent.h"
#include "FPSCamera.h"
#include "MeshRenderer.h"
#include "BallActor.h"
#include "BoxComponent.h"
#include "PlaneActor.h"
#include "Sword.h"

FPSActor::FPSActor(BaseScene* game)
	:ActorObject(game)
{
	mMoveComp = new MoveComponent(this);
	mAudioComp = new AudioComponent(this);
	mLastFootstep = 0.0f;
	mFootstep = mAudioComp->PlayEvent("event:/Footstep");
	mFootstep.SetPaused(true);

	mCameraComp = new FPSCamera(this);

	// �{�b�N�X�̓����蔻��̋@�\��ǉ�
	mBoxComp = new BoxComponent(this);
	AABB myBox(Vector3(-25.0f, -87.5f, -25.0f),
		Vector3(25.0f, 87.5f, 25.0f));
	mBoxComp->SetObjectBox(myBox);
	mBoxComp->SetShouldRotate(false);

	mSword = new Sword(game);
	Vector3 pos = GetPosition();
	mSword->SetPosition(pos);
	AddChildActor(mSword);
}

void FPSActor::UpdateActor(float deltaTime)
{
	ActorObject::UpdateActor(deltaTime);

	FixCollisions();

	// ������SE���Đ����鏈��
	mLastFootstep -= deltaTime;
	if ((!Math::NearZero(mMoveComp->GetForwardSpeed()) ||
		!Math::NearZero(mMoveComp->GetStrafeSpeed())) &&
		mLastFootstep <= 0.0f)
	{
		mFootstep.SetPaused(false);
		mFootstep.Restart();
		mLastFootstep = 0.5f;
	}
}

void FPSActor::ActorInput(const bool* keys)
{
	float forwardSpeed = 0.0f;
	float strafeSpeed = 0.0f;
	// wasd movement
	if (keys[SDL_SCANCODE_W])
	{
		forwardSpeed += 400.0f;
	}
	if (keys[SDL_SCANCODE_S])
	{
		forwardSpeed -= 400.0f;
	}
	if (keys[SDL_SCANCODE_A])
	{
		strafeSpeed -= 400.0f;
	}
	if (keys[SDL_SCANCODE_D])
	{
		strafeSpeed += 400.0f;
	}

	mMoveComp->SetForwardSpeed(forwardSpeed);
	mMoveComp->SetStrafeSpeed(strafeSpeed);

	//SDL�Ń}�E�X�̈ړ����l���擾
	float x, y;
	SDL_GetRelativeMouseState(&x, &y);
	//�}�E�X�ł̍ő�ړ����l��ݒ�
	const int maxMouseSpeed = 500;
	// �ő呬�x�ł̉�]/�b
	const float maxAngularSpeed = Math::Pi * 8;
	float angularSpeed = 0.0f;
	if (x != 0)
	{
		// [-1.0, 1.0]�ɕϊ�����
		angularSpeed = static_cast<float>(x) / maxMouseSpeed;
		// ��]/�b�Ŋ|����
		angularSpeed *= maxAngularSpeed;
	}
	mMoveComp->SetAngularSpeed(angularSpeed);

	// �������v�Z����
	const float maxPitchSpeed = Math::Pi * 8;
	float pitchSpeed = 0.0f;
	if (y != 0)
	{
		// [-1.0, 1.0]�ɕϊ�����
		pitchSpeed = static_cast<float>(y) / maxMouseSpeed;
		pitchSpeed *= maxPitchSpeed;
	}
	mCameraComp->SetPitchSpeed(pitchSpeed);

	//�q�I�u�W�F�N�g�������E�Z�b�g���鏈��(�e�X�g�p)
	if (keys[SDL_SCANCODE_O]) 
	{
		RemoveChildActor(mSword);
	}
	else if (keys[SDL_SCANCODE_P]) 
	{
		AddChildActor(mSword);
	}
}

void FPSActor::Shoot()
{
	// �X�^�[�g�|�C���g���擾����i�߂��̕��ʂ̉�ʂ̒��S�j
	Vector3 screenPoint(0.0f, 0.0f, 0.0f);
	Vector3 start = GetGame()->GetWinMain()->GetRenderer()->Unproject(screenPoint);
	// ��ʂ̒����A�߂��Ɖ����̊ԂɃG���h�|�C���g���擾���܂��B
	screenPoint.z = 0.9f;
	Vector3 end = GetGame()->GetWinMain()->GetRenderer()->Unproject(screenPoint);
	// �����x�N�g�����擾����
	Vector3 dir = end - start;
	dir.Normalize();
	// �{�[���𐶐�����
	BallActor* ball = new BallActor(GetGame());
	ball->SetPlayer(this);
	ball->SetPosition(start + dir * 20.0f);
	// �{�[������]�����ĐV����������������
	ball->RotateToNewForward(dir);
	// ���ˉ����Đ�����
	mAudioComp->PlayEvent("event:/Shot");
}

void FPSActor::SetFootstepSurface(float value)
{
	//�����ňꎞ��~���܂��B
	// FMOD�Ńp�����[�^�[��ݒ肵�����@��ύX����ƁA�������Đ�����邽��
	mFootstep.SetPaused(true);
	mFootstep.SetParameter("Surface", value);
}

void FPSActor::SetVisible(bool visible)
{
	mMeshComp->SetVisible(visible);
}

void FPSActor::FixCollisions()
{
	// ���[���h�{�b�N�X���X�V���邽�߂ɁA���[���h�ϊ����Čv�Z����K�v������܂��B
	ComputeWorldTransform();

	const AABB& playerBox = mBoxComp->GetWorldBox();
	Vector3 pos = GetPosition();

	auto& planes = GetGame()->GetPlanes();
	for (auto pa : planes)
	{
		for (unsigned int i = 0; i < pa->GetBoxs().size(); i++) {
			//PlaneActor�ƏՓˌ��m
			const AABB& planeBox = pa->GetBoxs()[i]->GetWorldBox();
			if (Intersect(playerBox, planeBox))
			{
				// �������̂��ׂĂ̈Ⴂ���v�Z���Ă�������
				float dx1 = planeBox.mMax.x - playerBox.mMin.x;
				float dx2 = planeBox.mMin.x - playerBox.mMax.x;
				float dy1 = planeBox.mMax.y - playerBox.mMin.y;
				float dy2 = planeBox.mMin.y - playerBox.mMax.y;
				float dz1 = planeBox.mMax.z - playerBox.mMin.z;
				float dz2 = planeBox.mMin.z - playerBox.mMax.z;

				// dx��dx1�܂���dx2�̂����A��Βl���Ⴂ���ɐݒ肵�܂��B
				float dx = Math::Abs(dx1) < Math::Abs(dx2) ?
					dx1 : dx2;
				// dy�ɂ��Ă����l�ł�
				float dy = Math::Abs(dy1) < Math::Abs(dy2) ?
					dy1 : dy2;
				// dz�ɂ��Ă����l�ł�
				float dz = Math::Abs(dz1) < Math::Abs(dz2) ?
					dz1 : dz2;

				// �ł��߂����ɉ�����x/y�ʒu�𒲐�����
				if (Math::Abs(dx) <= Math::Abs(dy) && Math::Abs(dx) <= Math::Abs(dz))
				{
					pos.x += dx;
				}
				else if (Math::Abs(dy) <= Math::Abs(dx) && Math::Abs(dy) <= Math::Abs(dz))
				{
					pos.y += dy;
				}
				else
				{
					pos.z += dz;
				}

				// �|�W�V������ݒ肵�A�{�b�N�X�R���|�[�l���g���X�V����K�v������܂��B
				SetPosition(pos);
				mBoxComp->OnUpdateWorldTransform();
			}

		}
	}
}