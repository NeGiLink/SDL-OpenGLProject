#pragma once
#include "Actor.h"
#include <string>

class YBotActor : public ActorObject
{
public:
	YBotActor(class BaseScene* game);
	void ActorInput(const bool* keys) override;
	void UpdateActor(float deltaTime) override;
private:
	enum State
	{
		TPose,
		Idle,
		Run,
		Jump,
		Capoeira
	};

	class SkeletalMeshRenderer* mMeshComp;

	class Animator* animator;

	class Sword* mSword;

	std::string animatorName = "YBot";
};

