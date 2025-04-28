#pragma once
#include "Actor.h"
#include "MeshRenderer.h"
#include "BoxCollider.h"
#include "Mesh.h"

//�f�o�b�O�X�e�[�W�𐶐�����N���X
class DebugStageActor : public ActorObject
{
public:
	DebugStageActor();
	std::vector<class BoxCollider*> GetBoxs() { return mBoxs; }
private:
	std::vector<class BoxCollider*> mBoxs;

	class MeshRenderer*				mMeshComp;
};

