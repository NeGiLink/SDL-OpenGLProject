#pragma once
#include "SoundEvent.h"
#include "Math.h"

// FMOD�w�b�_�[���܂߂�̂�����邽�߂̑O���錾
namespace FMOD
{
	class System;
	namespace Studio
	{
		class Bank;
		class EventDescription;
		class EventInstance;
		class System;
		class Bus;
	};
};

class AudioSystem
{
public:
	AudioSystem(class BaseScene* game);
	~AudioSystem();

	bool Initialize();
	void Shutdown();

	// Load/unload banks
	void LoadBank(const std::string& name);
	void UnloadBank(const std::string& name);
	void UnloadAllBanks();

	SoundEvent PlayEvent(const std::string& name);

	void Update(float deltaTime);

	// �|�W�V���i���I�[�f�B�I�p
	void SetListener(const Matrix4& viewMatrix);
	// ����o�X
	float GetBusVolume(const std::string& name) const;
	bool GetBusPaused(const std::string& name) const;
	void SetBusVolume(const std::string& name, float volume);
	void SetBusPaused(const std::string& name, bool pause);
protected:
	friend class SoundEvent;
	FMOD::Studio::EventInstance* GetEventInstance(unsigned int id);
private:
	// �C�x���g�C���X�^���X�Ɏg�p���鎟��ID��ǐ�
	static unsigned int													sNextID;

	class BaseScene*													mGame;
	// Map of loaded banks
	std::unordered_map<std::string, FMOD::Studio::Bank*>				mBanks;
	// �C�x���g���ƃC�x���g�����̃}�b�v
	std::unordered_map<std::string, FMOD::Studio::EventDescription*>	mEvents;
	// �C�x���gID����C�x���g�C���X�^���X�ւ̃}�b�v
	std::unordered_map<unsigned int, FMOD::Studio::EventInstance*>		mEventInstances;
	// Map of buses
	std::unordered_map<std::string, FMOD::Studio::Bus*>					mBuses;
	// FMOD studio system
	FMOD::Studio::System*												mSystem;
	// FMOD Low-level system (in case needed)
	FMOD::System*														mLowLevelSystem;
};