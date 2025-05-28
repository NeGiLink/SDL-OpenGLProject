#pragma once
#include "Math.h"
#include "StandardLibrary.h"

//��ʂ̕`��Ɋ֌W����ϐ����Ǘ����Ă���N���X
//��ʃT�C�Y�A�J�����̖ځA�^�[�Q�b�g�A�����A����p�A�Œ�E�ő�`�拗��
class WindowRenderProperty
{
private:
	//��ʃT�C�Y(��)
	static float		mWidth;
	//��ʃT�C�Y(�c)
	static float		mHeight;
	//�r���[���e�s��(�J�����̖�)
	static Vector3		mViewEye;
	//�r���[���e�s��(�J�����^�[�Q�b�g)
	static Vector3		mViewTarget;
	//�r���[���e�s��(�J��������)
	static Vector3		mViewUp;
	//����p
	static float		mFieldOfView;
	//�J�����̍Œ�`�拗��
	static float		mCameraNear;
	//�J�����̍ő�`�拗��
	static float		mCameraFar;
public:
	static float		GetWidth() { return mWidth; }

	static float		GetHeight() { return mHeight; }

	static Vector3		GetViewEye() { return mViewEye; }

	static Vector3		GetViewTarget() { return mViewTarget; }

	static Vector3		GetViewUp() { return mViewUp; }

	static float		GetFieldOfView() { return mFieldOfView; }

	static float		GetCameraNear() { return mCameraNear; }

	static float		GetCameraFar() { return mCameraFar; }

	static void			SetWindowScale(float width, float height);

	static void			SetViewEye(Vector3 eye);

	static void			SetViewTarget(Vector3 target);

	static void			SetViewUp(Vector3 up);

	static void			SetFieldOfView(float fieldOfView);

	static void			SetCameraNear(float cameraNear);

	static void			SetCameraFar(float cameraFar);
};

