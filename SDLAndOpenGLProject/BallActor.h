#pragma once
#include "Actor.h"

class BallActor : public ActorObject
{
public:
	BallActor(class BaseScene* game);

	void UpdateActor(float deltaTime) override;
	void SetPlayer(ActorObject* player);

	void HitTarget();
private:
	class AudioComponent* mAudioComp;
	class BallMove* mMyMove;
	float mLifeSpan;
};