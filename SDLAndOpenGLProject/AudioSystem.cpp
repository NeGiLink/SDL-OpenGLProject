#include "AudioSystem.h"
#include <SDL3/SDL_log.h>
#include <fmod_studio.hpp>
#include <fmod_errors.h>

unsigned int AudioSystem::sNextID = 0;

AudioSystem::AudioSystem(BaseScene* game)
	:mGame(game)
	, mSystem(nullptr)
	, mLowLevelSystem(nullptr)
{
}

AudioSystem::~AudioSystem()
{
}

bool AudioSystem::Initialize()
{
	// �f�o�b�O���O������������
	FMOD::Debug_Initialize(
		FMOD_DEBUG_LEVEL_ERROR, // Log only errors
		FMOD_DEBUG_MODE_TTY // Output to stdout
	);

	// FMOD�X�^�W�I�V�X�e���I�u�W�F�N�g���쐬
	FMOD_RESULT result;
	result = FMOD::Studio::System::create(&mSystem);
	if (result != FMOD_OK)
	{
		SDL_Log("Failed to create FMOD system: %s", FMOD_ErrorString(result));
		return false;
	}

	// FMOD�X�^�W�I�V�X�e����������
	result = mSystem->initialize(
		512, // ���������̍ő吔
		FMOD_STUDIO_INIT_NORMAL, // �f�t�H���g�ݒ���g�p����
		FMOD_INIT_NORMAL, // �f�t�H���g�ݒ���g�p����
		nullptr // �ʏ�͖���
	);
	if (result != FMOD_OK)
	{
		SDL_Log("Failed to initialize FMOD system: %s", FMOD_ErrorString(result));
		return false;
	}

	// �჌�x���V�X�e���|�C���^��ۑ�
	mSystem->getLowLevelSystem(&mLowLevelSystem);

	// �}�X�^�[�o���N�����[�h���܂��i�ŏ��ɕ�������j
	LoadBank(AudioBankProperty::GetMasterBankString());
	LoadBank(AudioBankProperty::GetMasterBank());

	return true;
}

void AudioSystem::Shutdown()
{
	// ���ׂẴo���N���A�����[�h���Ă�������
	UnloadAllBanks();
	// FMOD�V�X�e�����V���b�g�_�E��
	if (mSystem)
	{
		mSystem->release();
	}
}

void AudioSystem::LoadBank(const string& name)
{
	string path = AudioFile::AudioFilePath + name;
	// ��d���[�h��h��
	if (mBanks.find(path) != mBanks.end())
	{
		return;
	}

	// �o���N��ǂݍ������Ƃ��Ă�������
	FMOD::Studio::Bank* bank = nullptr;
	FMOD_RESULT result = mSystem->loadBankFile(
		path.c_str(), // �o���N�̃t�@�C����
		FMOD_STUDIO_LOAD_BANK_NORMAL, // �ʏ�̓ǂݍ���
		&bank // �o���N�ւ̃|�C���^��ۑ�����
	);

	const int maxPathLength = 512;
	if (result == FMOD_OK)
	{
		// map�Ƀo���N��ǉ�����
		mBanks.emplace(path, bank);
		// ���ׂĂ̔�X�g���[�~���O�T���v���f�[�^�����[�h����
		bank->loadSampleData();
		// ���̃o���N�̃C�x���g�����擾����
		int numEvents = 0;
		bank->getEventCount(&numEvents);
		if (numEvents > 0)
		{
			// ���̃o���N�̃C�x���g�̐����̃��X�g���擾���܂�
			vector<FMOD::Studio::EventDescription*> events(numEvents);
			bank->getEventList(events.data(), numEvents, &numEvents);
			char eventName[maxPathLength];
			for (int i = 0; i < numEvents; i++)
			{
				FMOD::Studio::EventDescription* e = events[i];
				// ���̃C�x���g�̃p�X���擾���܂�
				// �i��Fevent:/Explosion2D�j
				e->getPath(eventName, maxPathLength, nullptr);
				//�C�x���g��map�ɒǉ�
				mEvents.emplace(eventName, e);
			}
		}
		// ���̃o���N�ɂ���o�X�̐����擾���Ă�������
		int numBuses = 0;
		bank->getBusCount(&numBuses);
		if (numBuses > 0)
		{
			// ���̃o���N�̃o�X�̃��X�g���擾����
			vector<FMOD::Studio::Bus*> buses(numBuses);
			bank->getBusList(buses.data(), numBuses, &numBuses);
			char busName[512];
			for (int i = 0; i < numBuses; i++)
			{
				FMOD::Studio::Bus* bus = buses[i];
				// ���̃o�X�̃p�X���擾���Ă��������ibus:/SFX�̂悤�Ɂj
				bus->getPath(busName, 512, nullptr);
				//�o�X��map�ɒǉ�
				mBuses.emplace(busName, bus);
			}
		}
	}
}

void AudioSystem::UnloadBank(const string& name)
{
	string path = AudioFile::AudioFilePath + name;
	// Ignore if not loaded
	auto iter = mBanks.find(path);
	if (iter == mBanks.end())
	{
		return;
	}

	// First we need to remove all events from this bank
	FMOD::Studio::Bank* bank = iter->second;
	int numEvents = 0;
	bank->getEventCount(&numEvents);
	if (numEvents > 0)
	{
		// Get event descriptions for this bank
		vector<FMOD::Studio::EventDescription*> events(numEvents);
		// Get list of events
		bank->getEventList(events.data(), numEvents, &numEvents);
		char eventName[512];
		for (int i = 0; i < numEvents; i++)
		{
			FMOD::Studio::EventDescription* e = events[i];
			// Get the path of this event
			e->getPath(eventName, 512, nullptr);
			// Remove this event
			auto eventi = mEvents.find(eventName);
			if (eventi != mEvents.end())
			{
				mEvents.erase(eventi);
			}
		}
	}
	// Get the number of buses in this bank
	int numBuses = 0;
	bank->getBusCount(&numBuses);
	if (numBuses > 0)
	{
		// Get list of buses in this bank
		vector<FMOD::Studio::Bus*> buses(numBuses);
		bank->getBusList(buses.data(), numBuses, &numBuses);
		char busName[512];
		for (int i = 0; i < numBuses; i++)
		{
			FMOD::Studio::Bus* bus = buses[i];
			// Get the path of this bus (like bus:/SFX)
			bus->getPath(busName, 512, nullptr);
			// Remove this bus
			auto busi = mBuses.find(busName);
			if (busi != mBuses.end())
			{
				mBuses.erase(busi);
			}
		}
	}

	// Unload sample data and bank
	bank->unloadSampleData();
	bank->unload();
	// Remove from banks map
	mBanks.erase(iter);
}

void AudioSystem::UnloadAllBanks()
{
	for (auto& iter : mBanks)
	{
		// Unload the sample data, then the bank itself
		iter.second->unloadSampleData();
		iter.second->unload();
	}
	mBanks.clear();
	// No banks means no events
	mEvents.clear();
}

SoundEventClip AudioSystem::PlayEvent(const string& name)
{
	unsigned int retID = 0;
	auto iter = mEvents.find(name);
	if (iter != mEvents.end())
	{
		// Create instance of event
		FMOD::Studio::EventInstance* event = nullptr;
		iter->second->createInstance(&event);
		if (event)
		{
			// BGM�ASE���Đ�
			event->start();
			// Get the next id, and add to map
			sNextID++;
			retID = sNextID;
			mEventInstances.emplace(retID, event);
		}
	}
	return SoundEventClip(this, retID);
}

void AudioSystem::Update(float deltaTime)
{
	// Find any stopped event instances
	vector<unsigned int> done;
	for (auto& iter : mEventInstances)
	{
		FMOD::Studio::EventInstance* e = iter.second;
		// Get the state of this event
		FMOD_STUDIO_PLAYBACK_STATE state;
		e->getPlaybackState(&state);
		if (state == FMOD_STUDIO_PLAYBACK_STOPPED)
		{
			// Release the event and add id to done
			e->release();
			done.emplace_back(iter.first);
		}
	}

	// Remove done event instances from map
	for (auto id : done)
	{
		mEventInstances.erase(id);
	}

	// Update FMOD
	mSystem->update();
}

namespace
{
	FMOD_VECTOR VecToFMOD(const Vector3& in)
	{
		// Convert from our coordinates (+x forward, +y right, +z up)
		// to FMOD (+z forward, +x right, +y up)
		FMOD_VECTOR v;
		v.x = in.y;
		v.y = in.z;
		v.z = in.x;
		return v;
	}
}

void AudioSystem::SetListener(const Matrix4& viewMatrix)
{
	// Invert the view matrix to get the correct vectors
	Matrix4 invView = viewMatrix;
	invView.Invert();
	FMOD_3D_ATTRIBUTES listener;
	// Set position, forward, up
	listener.position = VecToFMOD(invView.GetTranslation());
	// In the inverted view, third row is forward
	listener.forward = VecToFMOD(invView.GetZAxis());
	// In the inverted view, second row is up
	listener.up = VecToFMOD(invView.GetYAxis());
	// Set velocity to zero (fix if using Doppler effect)
	listener.velocity = { 0.0f, 0.0f, 0.0f };
	// Send to FMOD
	mSystem->setListenerAttributes(0, &listener);
}

float AudioSystem::GetBusVolume(const string& name) const
{
	float retVal = 0.0f;
	const auto iter = mBuses.find(name);
	if (iter != mBuses.end())
	{
		iter->second->getVolume(&retVal);
	}
	return retVal;
}

bool AudioSystem::GetBusPaused(const string& name) const
{
	bool retVal = false;
	const auto iter = mBuses.find(name);
	if (iter != mBuses.end())
	{
		iter->second->getPaused(&retVal);
	}
	return retVal;
}

void AudioSystem::SetBusVolume(const string& name, float volume)
{
	auto iter = mBuses.find(name);
	if (iter != mBuses.end())
	{
		iter->second->setVolume(volume);
	}
}

void AudioSystem::SetBusPaused(const string& name, bool pause)
{
	auto iter = mBuses.find(name);
	if (iter != mBuses.end())
	{
		iter->second->setPaused(pause);
	}
}

FMOD::Studio::EventInstance* AudioSystem::GetEventInstance(unsigned int id)
{
	FMOD::Studio::EventInstance* event = nullptr;
	auto iter = mEventInstances.find(id);
	if (iter != mEventInstances.end())
	{
		event = iter->second;
	}
	return event;
}
