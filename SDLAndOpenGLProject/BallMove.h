#pragma once
#include "MoveComponent.h"

//�e�̈ړ������Ɏg�p���Ă���
//���݂͖��g�p
class BallMove : public MoveComponent
{
public:
	BallMove(class ActorObject* owner);

	void SetPlayer(ActorObject* player) { mPlayer = player; }
	void Update(float deltaTime) override;
protected:
	class ActorObject* mPlayer;
};

