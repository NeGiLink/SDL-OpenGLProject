#pragma once
#include "Math.h"
#include "Actor.h"

//�X�P���^�����f���̃{�[���̃g�����X�t�H�[���N���X
class BoneTransform
{
public:
	Matrix4 ToMatrix() const;

	void FromMatrix(Matrix4& mat);

	static BoneTransform Interpolate(const BoneTransform& a, const BoneTransform& b, float f);

	// ����̓f�[�^�����J�ɂ��Ă��܂��B
	//�܂���X�����͂���\��ł��B
	Vector3			mScale;

	Quaternion		mRotation;
	
	Vector3			mPosition;
};