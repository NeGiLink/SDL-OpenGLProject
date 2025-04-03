#pragma once
#include "Actor.h"
#include <string>

class TestCharacter : public ActorObject
{
public:
	TestCharacter(class BaseScene* game);

	void ActorInput(const bool* keys) override;
private:
	enum State
	{
		Idle,
		Capoeira
	};

	class SkeletalMeshRenderer* mMeshComp;

	class Animator* animator;

	std::string animatorName = "TestCharacter";
};

