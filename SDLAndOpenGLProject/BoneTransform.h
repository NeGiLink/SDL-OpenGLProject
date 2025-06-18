#pragma once
#include "Math.h"
#include "Actor.h"


/*
* ===�G���W����������/Engine internal processing===
*/

//���Ќ������������t�@�C��
//�X�P���^�����f���̃{�[���̃g�����X�t�H�[���N���X
//�{�[���̈ʒu�A��]�A�X�P�[�����O���Ǘ�����N���X
class BoneTransform
{
private:
	// ����̓f�[�^�����J�ɂ��Ă��܂��B
	//�܂���X�����͂���\��ł��B
	Vector3					mScale;

	Quaternion				mRotation;
	
	Vector3					mPosition;
public:
	Matrix4					ToMatrix() const;

	void					FromMatrix(Matrix4& mat);

	static BoneTransform	Interpolate(const BoneTransform& a, const BoneTransform& b, float f);

	Vector3					GetScale() { return mScale; }

	void					SetScale(Vector3 scale) { mScale = scale; }

	Quaternion				GetRotation() { return mRotation; }

	void					SetRotation(Quaternion rotation) { mRotation = rotation; }

	Vector3					GetPosition() { return mPosition; }

	void					SetPosition(Vector3 position) { mPosition = position; }
};