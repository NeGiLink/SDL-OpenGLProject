#pragma once
#include "Actor.h"
//���g�p
//����g�p�o����悤�ɂ��邽�߂Ɏc���Ă��܂��B
class BallActor : public ActorObject
{
public:
	BallActor(class BaseScene* game);

	void UpdateActor(float deltaTime) override;

	void SetPlayer(ActorObject* player);

	void HitTarget();
private:
	class AudioComponent*	mAudioComp;

	class BallMove*			mMyMove;
	
	float					mLifeSpan;
};