#pragma once
#include "Actor.h"
#include "Mesh.h"
#include "SkeletalMeshRenderer.h"
#include "Animator.h"
#include "BoxCollider.h"
#include "Sword.h"
#include "CubeActor.h"


class SmallCharacter : public ActorObject
{
public:
										SmallCharacter();

	void								ActorInput(const struct InputState& keys) override;
private:
	enum State
	{
		Idle,
		Run,
		Jump,
		Capoeira,
		TPose
	};

	class SkeletalMeshRenderer*			mSkeletonMesh;

	class Animator*						animator;

	class Sword*						mSword;

	string								animatorName = "SmallCharacter";
};