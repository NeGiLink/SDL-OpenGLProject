#pragma once
#include "Math.h"

//���Ќ��̃t�@�C��
//�����_���o�͂��Ǘ�����N���X
class Random
{
private:
	static std::mt19937 sGenerator;
public:
	static void Init();

	// �w�肳�ꂽ�����ŃW�F�l���[�^�[���V�[�h���܂�
	// ���ӁF�ʏ�A�蓮�Ŏg�p����K�v�͂���܂���B
	static void			Seed(unsigned int seed);

	// 0.0f����1.0f�̊Ԃ̕��������_�����擾�B
	static float		GetFloat();

	// �w�肳�ꂽ�͈͂��畂�������_�����擾
	static float		GetFloatRange(float min, float max);

	// �w�肳�ꂽ�͈͂��琮�����擾
	static int			GetIntRange(int min, int max);

	// �ŏ�/�ő�͈̔͂��l�����ă����_���ȃx�N�g�����擾
	static Vector2		GetVector(const Vector2& min, const Vector2& max);
	static Vector3		GetVector(const Vector3& min, const Vector3& max);

};