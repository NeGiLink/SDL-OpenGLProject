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

	std::vector<class BoxCollider*> GetBoxs() { return mBoxs; }

	void ActorInput(const struct InputState& keys) override;

private:
	//AABB�̃R���C�_�[
	std::vector<class BoxCollider*> mBoxs;
	//�e�X�g�悤�ɗp�ӂ����ړ��@�\
	PushButtonMove* mPushButtonMove;
};

