#pragma once
#include "Actor.h"
#include "MeshRenderer.h"
#include "BoxCollider.h"
#include "Mesh.h"
#include "TargetComponent.h"

//的オブジェクトのクラス
class TargetActor : public ActorObject
{
public:
	TargetActor();
private:
	vector<class BoxCollider*>		mBoxs;

	class MeshRenderer*					mMeshComp;
};