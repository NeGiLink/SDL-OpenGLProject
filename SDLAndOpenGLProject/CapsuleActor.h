#pragma once
#include "Actor.h"
#include "MeshRenderer.h"
#include "CapsuleCollider.h"
#include "Mesh.h"

//�J�v�Z���^�̃I�u�W�F�N�g
//Unity�̂悤�Ƀf�t�H���g�ō쐬�\�I�u�W�F�N�g
class CapsuleActor : public ActorObject
{
public:
	CapsuleActor();

	class CapsuleCollider* GetCapsule() { return mCapsule; }
private:
	//�J�v�Z���R���C�_�[
	class CapsuleCollider* mCapsule;
};