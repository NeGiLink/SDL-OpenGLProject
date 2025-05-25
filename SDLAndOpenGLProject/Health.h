#pragma once
#include "Actor.h"
#include "MeshRenderer.h"
#include "BoxCollider.h"
#include "Mesh.h"

//�@�\�e�X�g�p�̃I�u�W�F�N�g
//�v���C���[��HP���񕜂����邽�߂̃I�u�W�F�N�g
class HealthObject : public ActorObject
{
private:
	vector<class BoxCollider*>		mBoxs;
public:
									HealthObject();

	void							UpdateActor(float deltaTime)override;

	vector<class BoxCollider*>		GetBoxs() { return mBoxs; }
};

