#pragma once
#include "Actor.h"
#include "MeshRenderer.h"
#include "BoxCollider.h"
#include "Mesh.h"
#include "TargetComponent.h"

//�I�I�u�W�F�N�g�̃N���X
class TargetActor : public ActorObject
{
private:
	vector<class BoxCollider*>			mBoxs;

	class MeshRenderer*					mMeshComp;
public:
										TargetActor();
};