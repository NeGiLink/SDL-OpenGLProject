#pragma once
#include "Actor.h"
#include <string>

//�e�X�g�p��3D���f����ǂݍ���ł���N���X
//���O�͂ǂ̃��f����������₷�����邽�߂ɂ��̖��O�ɂ��܂����B
class YBotActor : public ActorObject
{
public:
	YBotActor();
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

	class SkeletalMeshRenderer*		mSkeletonMesh;

	class Animator*					animator;

	class Sword*					mSword;

	std::string						animatorName = "YBot";
};

