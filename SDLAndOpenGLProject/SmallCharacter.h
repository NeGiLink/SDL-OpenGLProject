#pragma once
#include "Actor.h"
#include "Mesh.h"
#include "SkeletalMeshRenderer.h"
#include "Animator.h"
#include "BoxCollider.h"
#include "Sword.h"


class SmallCharacter : public ActorObject
{
public:
	SmallCharacter();

	void ActorInput(const struct InputState& keys) override;
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

	class SkeletalMeshRenderer*			mMeshComp;

	class Animator*						animator;

	class Sword*						mSword;

	std::string							animatorName = "SmallCharacter";
};