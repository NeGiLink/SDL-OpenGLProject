#pragma once
#include "Actor.h"
#include "Mesh.h"
#include "SkeletalMeshRenderer.h"
#include "Animator.h"
#include "BoxCollider.h"
#include "Sword.h"

//�e�X�g�p��3D���f����ǂݍ���ł���N���X
//���O�͂ǂ̃��f����������₷�����邽�߂ɂ��̖��O�ɂ��܂����B
class YBotActor : public ActorObject
{
public:
	YBotActor();
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

	class Sword*					mSword;

	string							animatorName = "YBot";
	
};

