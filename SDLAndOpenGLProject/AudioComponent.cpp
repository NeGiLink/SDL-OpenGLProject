#include "AudioComponent.h"
#include "Actor.h"
#include "BaseScene.h"
#include "AudioSystem.h"

AudioComponent::AudioComponent(ActorObject* owner, int updateOrder)
	:Component(owner, updateOrder)
{
}

AudioComponent::~AudioComponent()
{
	StopAllEvents();
}

void AudioComponent::Update(float deltaTime)
{
	Component::Update(deltaTime);

	// ������2D�C�x���g���폜����
	auto iter = mEvents2D.begin();
	while (iter != mEvents2D.end())
	{
		if (!iter->IsValid())
		{
			iter = mEvents2D.erase(iter);
		}
		else
		{
			++iter;
		}
	}

	// ������3D�C�x���g���폜����
	iter = mEvents3D.begin();
	while (iter != mEvents3D.end())
	{
		if (!iter->IsValid())
		{
			iter = mEvents3D.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}

void AudioComponent::OnUpdateWorldTransform()
{
	// 3D�C�x���g�̐��E���ς��A�v�f
	Matrix4 world = mOwner->GetWorldTransform();
	for (auto& event : mEvents3D)
	{
		if (event.IsValid())
		{
			event.Set3DAttributes(world);
		}
	}
}

SoundEventClip AudioComponent::LoadAudio(const string& name)
{
	SoundEventClip e = mOwner->GetGame()->GetAudioSystem()->PlayEvent(name);
	// 2D or 3D?
	if (e.Is3D())
	{
		mEvents3D.emplace_back(e);
		// ������3D������ݒ肷��
		e.Set3DAttributes(mOwner->GetWorldTransform());
	}
	else
	{
		mEvents2D.emplace_back(e);
	}
	return e;
}

void AudioComponent::StopAllEvents()
{
	// ���ׂẲ����~
	for (auto& e : mEvents2D)
	{
		e.Stop();
	}
	for (auto& e : mEvents3D)
	{
		e.Stop();
	}
	// �C�x���g���N���A
	mEvents2D.clear();
	mEvents3D.clear();
}