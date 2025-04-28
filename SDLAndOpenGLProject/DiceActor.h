#pragma once
#include "Actor.h"
#include "MeshRenderer.h"
#include "BoxCollider.h"
#include "Mesh.h"

//���f�����e�X�g�ǂݍ��݂��Ă���N���X
class DiceActor : public ActorObject
{
public:
	DiceActor();

	std::vector<class BoxCollider*> GetBoxs() { return mBoxs; }
private:
	std::vector<class BoxCollider*> mBoxs;

	Vector3							mPos;
};

