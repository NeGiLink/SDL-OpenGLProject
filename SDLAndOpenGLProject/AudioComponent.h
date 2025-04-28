#pragma once
#include "Component.h"
#include "SoundEvent.h"
#include <vector>
#include <string>

//オーディオ機能をまとめたクラス
//3D、2Dのオーディオ処理を行う
class AudioComponent : public Component
{
public:
	AudioComponent(class ActorObject* owner, int updateOrder = 200);
	~AudioComponent();

	void Update(float deltaTime) override;
	void OnUpdateWorldTransform() override;

	SoundEvent PlayEvent(const std::string& name);
	void StopAllEvents();
private:
	std::vector<SoundEvent> mEvents2D;
	std::vector<SoundEvent> mEvents3D;
};