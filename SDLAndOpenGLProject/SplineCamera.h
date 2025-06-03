#pragma once
#include "BaseCamera.h"
#include "Actor.h"

//���Е����̃t�@�C��
struct Spline
{
	// �X�v���C���̐���_�i
	// �Z�O�����g���̓_�̐���n�Ƃ���ƁAn+2�̃|�C���g���K�v�j
	vector<Vector3> mControlPoints;
	// �J�n�C���f�b�N�X��P1�ł���X�v���C���Z�O�����g���l�����āA
	// t�l�Ɋ�Â��Ĉʒu���v�Z���܂��B
	Vector3			Compute(size_t startIdx, float t) const;
	// ����_�̐���Ԃ��܂��B
	size_t			GetNumPoints() const { return mControlPoints.size(); }
};

class SplineCamera : public BaseCamera
{
private:
	// �X�v���C���p�X�ɉ����ăJ�������ړ����܂�
	Spline	mPath;
	// ���݂̐���|�C���g�C���f�b�N�X��t
	size_t	mIndex;
	float	mT;
	// �ʂ̕ω�/�b
	float	mSpeed;
	// �J�������o�H�ɉ����Ĉړ������邩�ǂ���
	bool	mPaused;
public:
			SplineCamera(class ActorObject* owner);

	void	Update(float deltaTime) override;
	// �X�v���C�����ċN�����Ă�������
	void	Restart();

	void	SetSpeed(float speed) { mSpeed = speed; }
	void	SetSpline(const Spline& spline) { mPath = spline; }
	void	SetPaused(bool pause) { mPaused = pause; }
};