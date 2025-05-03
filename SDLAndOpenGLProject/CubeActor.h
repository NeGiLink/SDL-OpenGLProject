#pragma once
#include "Actor.h"
#include "MeshRenderer.h"
#include "BoxCollider.h"
#include "PushButtonMove.h"
#include "Mesh.h"

//���^�̃I�u�W�F�N�g
//Unity�̂悤�Ƀf�t�H���g�ō쐬�\�I�u�W�F�N�g
class CubeActor : public ActorObject
{
public:
	CubeActor();

	vector<class BoxCollider*> GetBoxs() { return mBoxs; }

private:
	//AABB�̃R���C�_�[
	vector<class BoxCollider*> mBoxs;
};

