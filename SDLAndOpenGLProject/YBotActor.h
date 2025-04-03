#pragma once
#include "Actor.h"
#include <string>

class YBotActor : public ActorObject
{
public:
	YBotActor(class BaseScene* game);
	void ActorInput(const bool* keys) override;
private:
	enum State
	{
		Idle,
		Capoeira
	};

	class SkeletalMeshRenderer* mMeshComp;

	class Animator* animator;

	std::string animatorName = "YBot";
};

