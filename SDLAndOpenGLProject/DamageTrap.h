#pragma once
#include "Actor.h"
#include "MeshRenderer.h"
#include "BoxCollider.h"
#include "Mesh.h"

//�e�X�g�p�̃_���[�W�I�u�W�F�N�g
//�v���C���[�����̃I�u�W�F�N�g�ɓ����������Ƀ_���[�W��^���邽�߂̂���
class DamageTrap : public ActorObject
{
private:
	vector<class BoxCollider*>		mBoxs;
public:
	DamageTrap();

	vector<class BoxCollider*>		GetBoxs() { return mBoxs; }
};

