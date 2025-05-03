#include "SplineCamera.h"

Vector3 Spline::Compute(size_t startIdx, float t) const
{
	// startIdx���͈͊O�ł��邩�m�F���Ă�������
	if (startIdx >= mControlPoints.size())
	{
		return mControlPoints.back();
	}
	else if (startIdx == 0)
	{
		return mControlPoints[startIdx];
	}
	else if (startIdx + 2 >= mControlPoints.size())
	{
		return mControlPoints[startIdx];
	}

	// p0����p3���擾����
	Vector3 p0 = mControlPoints[startIdx - 1];
	Vector3 p1 = mControlPoints[startIdx];
	Vector3 p2 = mControlPoints[startIdx + 1];
	Vector3 p3 = mControlPoints[startIdx + 2];
	// �L���g�}���E�����������ɏ]���Ĉʒu���v�Z����
	Vector3 position = 0.5f * ((2.0f * p1) + (-1.0f * p0 + p2) * t +
		(2.0f * p0 - 5.0f * p1 + 4.0f * p2 - p3) * t * t +
		(-1.0f * p0 + 3.0f * p1 - 3.0f * p2 + p3) * t * t * t);
	return position;
}

SplineCamera::SplineCamera(ActorObject* owner)
	:BaseCamera(owner)
	, mIndex(1)
	, mT(0.0f)
	, mSpeed(0.5f)
	, mPaused(true)
{
}

void SplineCamera::Update(float deltaTime)
{
	BaseCamera::Update(deltaTime);
	// t�l���X�V����
	if (!mPaused)
	{
		mT += mSpeed * deltaTime;
		// �K�v�ł���΁A���̃R���g���[���|�C���g�ɐi�ށB
		// �X�s�[�h���������Ĉ�t���[�����ɕ����̃R���g���[���|�C���g���щz���Ă��܂����Ƃ͂Ȃ��Ɖ���B
		if (mT >= 1.0f)
		{
			// �i�ނ��߂̃|�C���g�����邱�Ƃ��m�F�B
			if (mIndex < mPath.GetNumPoints() - 3)
			{
				mIndex++;
				mT = mT - 1.0f;
			}
			else
			{
				//�ꎞ��~�B
				mPaused = true;
			}
		}
	}

	// �J�����̈ʒu�͌��݂�t/�C���f�b�N�X�ɂ�����X�v���C���ł��B
	Vector3 cameraPos = mPath.Compute(mIndex, mT);
	// �^�[�Q�b�g�|�C���g�̓X�v���C���̑O�ɂ킸���ɏ����ȃf���^�ł��B
	Vector3 target = mPath.Compute(mIndex, mT + 0.01f);
	// �X�v���C�����t���܂ɂȂ�Ȃ��Ɖ���B
	const Vector3 up = Vector3::UnitZ;
	Matrix4 view = Matrix4::CreateLookAt(cameraPos, target, up);
	SetViewMatrix(view);
}

void SplineCamera::Restart()
{
	mIndex = 1;
	mT = 0.0f;
	mPaused = false;
}