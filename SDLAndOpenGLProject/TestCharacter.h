#pragma once
#include "Actor.h"
#include "Mesh.h"
#include "SkeletalMeshRenderer.h"
#include "Animator.h"
#include "BoxCollider.h"
#include "Sword.h"

//�e�X�g�p�ɐ������Ă�3D�L�����N�^�[�̂�����̂̃N���X
class TestCharacter : public ActorObject
{
public:
	TestCharacter();

	void ActorInput(const struct InputState& keys) override;
private:
	enum State
	{
		Idle,
		Run,
		Jump,
		Capoeira,
		TPose
	};

	class SkeletalMeshRenderer*		mSkeletonMesh;

	class Animator*					animator;

	class BoxCollider*				mBoxComp;

	class Sword*					mSword;

	string							animatorName = "TestCharacter";
};