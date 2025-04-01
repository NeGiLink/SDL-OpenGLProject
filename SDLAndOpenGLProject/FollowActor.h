#pragma once
#include "Actor.h"
#include <string>

class FollowActor : public ActorObject
{
public:
	FollowActor(class WinMain* game);

	void ActorInput(const bool* keys) override;

	void SetVisible(bool visible);
private:

	enum State
	{
		Idle,
		Run
	};

	class MoveComponent* mMoveComp;
	class FollowCamera* mCameraComp;
	class SkeletalMeshComponent* mMeshComp;
	class Animator* animator;
	bool mMoving;

	std::string animatorName = "FollowActor";
};

