#pragma once
#include "Actor.h"

//FBX�t�@�C����2�̃��f�����ꏏ�ɂ���������
//�ǂݍ��݂��m�F���邽�߂̃N���X
class TwoObjectActor : public ActorObject
{
public:
	TwoObjectActor(class BaseScene* game);
	void UpdateActor(float deltaTime) override;
};

