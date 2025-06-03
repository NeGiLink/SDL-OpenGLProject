#pragma once
#include "SDOpenLib.h"

//���Ќ������������t�@�C��
//SE,BGM���Đ�����N���X
//AudioSystem���ɂ���AudioBank����
//BGM�ASE���擾�Đ�����
//�擾�㎩���ōĐ������悤�ɂȂ��Ă���
class SoundEventClip
{
protected:
	// ���̃R���X�g���N�^��protected�ɂ��AAudioSystem��F�B�Ƃ��Đݒ肵�āA
	// AudioSystem�݂̂����̃R���X�g���N�^�ɃA�N�Z�X�ł���悤�ɂ��܂��B
	friend class		AudioSystem;
						SoundEventClip(class AudioSystem* system, unsigned int id);
private:
	class AudioSystem*	mSystem;
	unsigned int		mID;
public:
						SoundEventClip();
	// �֘A����FMOD�C�x���g���܂����݂���ꍇ�Atrue��Ԃ��܂��B
	bool				IsValid();
	// �C�x���g���ŏ�����ċN������B
	void				ResetStart();
	// ���̃C�x���g���~�B
	void				Stop(bool allowFadeOut = true);
	// Setters
	//�I�[�f�B�I�̈ꎞ��~�A�Đ����s���֐�
	void				SetPaused(bool pause);
	//�ꎞ��~�����o����֐�
	void				Pause();
	//��~����������ĊJ�o����֐�
	void				Restart();
	void				SetVolume(float value);
	void				SetPitch(float value);
	void				SetParameter(const string& name, float value);
	// Getters
	bool				GetPaused() const;
	float				GetVolume() const;
	float				GetPitch() const;
	float				GetParameter(const string& name);
	// Positional
	bool				Is3D() const;
	void				Set3DAttributes(const Matrix4& worldTrans);
};