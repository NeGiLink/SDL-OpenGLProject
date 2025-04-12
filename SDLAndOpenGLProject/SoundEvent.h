#pragma once
#include <string>
#include "Math.h"

//SE,BGM���擾�E�Đ�����N���X
class SoundEvent
{
public:
	SoundEvent();
	// �֘A����FMOD�C�x���g���܂����݂���ꍇ�Atrue��Ԃ��܂��B
	bool IsValid();
	// �C�x���g���ŏ�����ċN������B
	void Restart();
	// ���̃C�x���g���~�B
	void Stop(bool allowFadeOut = true);
	// Setters
	void SetPaused(bool pause);
	void SetVolume(float value);
	void SetPitch(float value);
	void SetParameter(const std::string& name, float value);
	// Getters
	bool GetPaused() const;
	float GetVolume() const;
	float GetPitch() const;
	float GetParameter(const std::string& name);
	// Positional
	bool Is3D() const;
	void Set3DAttributes(const Matrix4& worldTrans);
protected:
	// ���̃R���X�g���N�^��protected�ɂ��AAudioSystem��F�B�Ƃ��Đݒ肵�āA
	// AudioSystem�݂̂����̃R���X�g���N�^�ɃA�N�Z�X�ł���悤�ɂ��܂��B
	friend class AudioSystem;
	SoundEvent(class AudioSystem* system, unsigned int id);
private:
	class AudioSystem* mSystem;
	unsigned int mID;
};