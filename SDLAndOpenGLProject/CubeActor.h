#pragma once
#include "Actor.h"
#include "MeshRenderer.h"
#include "BoxCollider.h"
#include "PushButtonMove.h"
#include "Mesh.h"

//箱型のオブジェクト
//Unityのようにデフォルトで作成可能オブジェクト
class CubeActor : public ActorObject
{
public:
	CubeActor();

	vector<class BoxCollider*> GetBoxs() { return mBoxs; }

private:
	//AABBのコライダー
	vector<class BoxCollider*> mBoxs;
};

