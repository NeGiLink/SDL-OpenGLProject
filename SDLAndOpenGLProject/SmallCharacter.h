#pragma once
#include "Actor.h"
#include <string>


class SmallCharacter : public ActorObject
{
public:
	SmallCharacter(class BaseScene* game);

	void ActorInput(const bool* keys) override;
	void UpdateActor(float deltaTime) override;
private:
	enum State
	{
		Idle,
		Run,
		Jump,
		Capoeira,
		TPose
	};

	class SkeletalMeshRenderer* mMeshComp;

	class Animator* animator;

	class Sword* mSword;

	std::string animatorName = "SmallCharacter";
};