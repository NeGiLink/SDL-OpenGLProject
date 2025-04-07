#pragma once
#include "Actor.h"
#include <string>

class TestCharacter : public ActorObject
{
public:
	TestCharacter(class BaseScene* game);

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

	std::string animatorName = "TestCharacter";
};