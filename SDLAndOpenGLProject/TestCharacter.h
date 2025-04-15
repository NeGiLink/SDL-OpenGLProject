#pragma once
#include "Actor.h"
#include <string>

//テスト用に生成してる3Dキャラクターのうち一体のクラス
class TestCharacter : public ActorObject
{
public:
	TestCharacter(class BaseScene* game);

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

	class SkeletalMeshRenderer*		mMeshComp;

	class Animator*					animator;

	class Sword*					mSword;

	std::string						animatorName = "TestCharacter";
};