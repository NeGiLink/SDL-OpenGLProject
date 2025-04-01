#pragma once
#include "Actor.h"
#include <string>

class TestCharacter : public ActorObject
{
public:
	TestCharacter(class WinMain* game);

	void ActorInput(const bool* keys) override;
private:
	enum State
	{
		Idle,
		Capoeira
	};

	class SkeletalMeshComponent* mMeshComp;

	class Animator* animator;

	std::string animatorName = "TestCharacter";
};

