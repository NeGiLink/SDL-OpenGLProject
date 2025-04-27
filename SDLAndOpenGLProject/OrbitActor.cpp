#include "OrbitActor.h"


OrbitActor::OrbitActor()
	:ActorObject()
{
	mMeshComp = new MeshRenderer(this);
	mMeshComp->SetMesh(GetGame()->GetWinMain()->GetRenderer()->GetMesh("RacingCar.gpmesh"));
	SetPosition(Vector3(0.0f, 0.0f, -100.0f));

	mCameraComp = new OrbitCamera(this);
}

void OrbitActor::ActorInput(const struct InputState& keys)
{
	//�}�E�X��]SDL����̑��ΓI�ȓ������擾
	float x, y;
	Uint64 buttons = SDL_GetRelativeMouseState(&x, &y);
	// �E�N���b�N��������Ă���ꍇ�ɂ̂݉�]��K�p����
	if (buttons & SDL_BUTTON_MASK(SDL_BUTTON_RIGHT))
	{
		// �}�E�X�̓����͒ʏ�-500����+500�̊Ԃł���Ɖ��肵�܂��B
		const int maxMouseSpeed = 500;
		// �ő呬�x�ł̉�]/�b
		const float maxOrbitSpeed = Math::Pi * 8;
		float yawSpeed = 0.0f;
		if (x != 0)
		{
			// [-1.0, 1.0]�ɕϊ�����
			yawSpeed = static_cast<float>(x) / maxMouseSpeed;
			// ��]/�b�Ŋ|����
			yawSpeed *= maxOrbitSpeed;
		}
		mCameraComp->SetYawSpeed(-yawSpeed);

		// �������v�Z����
		float pitchSpeed = 0.0f;
		if (y != 0)
		{
			// [-1.0, 1.0]�ɕϊ�����
			pitchSpeed = static_cast<float>(y) / maxMouseSpeed;
			pitchSpeed *= maxOrbitSpeed;
		}
		mCameraComp->SetPitchSpeed(pitchSpeed);
	}
}

void OrbitActor::SetVisible(bool visible)
{
	mMeshComp->SetVisible(visible);
}