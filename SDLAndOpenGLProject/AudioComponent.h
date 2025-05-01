#pragma once
#include "Component.h"
#include "SoundEvent.h"
#include <vector>
#include <string>

//�I�[�f�B�I�@�\���܂Ƃ߂��N���X
//3D�A2D�̃I�[�f�B�I�������s��
class AudioComponent : public Component
{
public:
	AudioComponent(class ActorObject* owner, int updateOrder = 200);
	~AudioComponent();

	void Update(float deltaTime) override;
	void OnUpdateWorldTransform() override;

	SoundEvent PlayEvent(const string& name);
	void StopAllEvents();
private:
	vector<SoundEvent> mEvents2D;
	vector<SoundEvent> mEvents3D;
};