#pragma once
#include "Actor.h"
#include "MeshRenderer.h"
#include "BoxCollider.h"
#include "Mesh.h"

//デバッグステージを生成するクラス
class DebugStageActor : public ActorObject
{
private:
	vector<class BoxCollider*>		mBoxs;

	class MeshRenderer*				mMeshComp;
public:
									DebugStageActor();
	vector<class BoxCollider*>		GetBoxs() { return mBoxs; }
};

