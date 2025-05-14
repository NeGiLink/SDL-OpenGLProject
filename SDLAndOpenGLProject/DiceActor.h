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

	vector<class BoxCollider*>		GetBoxs() { return mBoxs; }
private:
	vector<class BoxCollider*>		mBoxs;

	Vector3							mPos;
};

