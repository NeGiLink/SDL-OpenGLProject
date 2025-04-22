#pragma once
#include "Actor.h"

//���f�����e�X�g�ǂݍ��݂��Ă���N���X
class DiceActor : public ActorObject
{
public:
	DiceActor();

	std::vector<class BoxCollider*> GetBoxs() { return mBoxs; }

	void UpdateActor(float deltaTime) override;

	void ActorInput(const struct InputState& keys) override;

	void OnCollisionEnter(class ActorObject* target) override;
private:
	std::vector<class BoxCollider*> mBoxs;

	Vector3				mPos;
};

