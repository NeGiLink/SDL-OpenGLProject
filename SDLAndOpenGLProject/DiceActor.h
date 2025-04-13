#pragma once
#include "Actor.h"

//���f�����e�X�g�ǂݍ��݂��Ă���N���X
class DiceActor : public ActorObject
{
public:
	DiceActor(class BaseScene* game);

	std::vector<class BoxCollider*> GetBoxs() { return mBoxs; }

	void OnCollisionEnter(class ActorObject* target) override;
private:
	std::vector<class BoxCollider*> mBoxs;
};

