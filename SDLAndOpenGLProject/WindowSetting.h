#pragma once
#include "StandardLibrary.h"

//��ʃT�C�Y
namespace Window
{
	//��ʃT�C�Y(��)
	static float Width = 1280.0f;
	//��ʃT�C�Y(�c)
	static float Height = 768.0f;
	//�r���[���e�s��(�J�����̖�)
	static Vector3 ViewEye = Vector3::Zero;
	//�r���[���e�s��(�J�����^�[�Q�b�g)
	static Vector3 ViewTarget = Vector3::UnitX;
	//�r���[���e�s��(�J��������)
	static Vector3 ViewUp = Vector3::UnitZ;
	//����p
	static float FieldOfView = 70.0f;
	//�J�����̍Œ�`�拗��
	static float CameraNear = 0.1f;
	//�J�����̍ő�`�拗��
	static float CameraFar = 10000.0f;
}