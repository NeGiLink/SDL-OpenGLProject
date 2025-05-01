#pragma once
#include "SoundEvent.h"
#include "Math.h"
#include "Typedefs.h"

// FMODヘッダーを含めるのを避けるための前方宣言
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
	void LoadBank(const string& name);
	void UnloadBank(const string& name);
	void UnloadAllBanks();

	SoundEvent PlayEvent(const string& name);

	void Update(float deltaTime);

	// ポジショナルオーディオ用
	void SetListener(const Matrix4& viewMatrix);
	// 制御バス
	float GetBusVolume(const string& name) const;
	bool GetBusPaused(const string& name) const;
	void SetBusVolume(const string& name, float volume);
	void SetBusPaused(const string& name, bool pause);
protected:
	friend class SoundEvent;
	FMOD::Studio::EventInstance* GetEventInstance(unsigned int id);
private:
	// イベントインスタンスに使用する次のIDを追跡
	static unsigned int													sNextID;

	class BaseScene*													mGame;
	// Map of loaded banks
	std::unordered_map<string, FMOD::Studio::Bank*>				mBanks;
	// イベント名とイベント説明のマップ
	std::unordered_map<string, FMOD::Studio::EventDescription*>	mEvents;
	// イベントIDからイベントインスタンスへのマップ
	std::unordered_map<unsigned int, FMOD::Studio::EventInstance*>		mEventInstances;
	// Map of buses
	std::unordered_map<string, FMOD::Studio::Bus*>					mBuses;
	// FMOD studio system
	FMOD::Studio::System*												mSystem;
	// FMOD Low-level system (in case needed)
	FMOD::System*														mLowLevelSystem;
};