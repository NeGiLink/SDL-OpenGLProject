#pragma once
#include "Actor.h"
#include <string>

//�e�X�g�p�ɐ������Ă�3D�L�����N�^�[�̂�����̂̃N���X
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