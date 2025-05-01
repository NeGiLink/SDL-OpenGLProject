#pragma once
#include "Actor.h"
#include "MeshRenderer.h"
#include "BoxCollider.h"
#include "Mesh.h"

//平面型のオブジェクト
//Unityのようにデフォルトで作成可能オブジェクト
class PlaneActor : public ActorObject
{
public:
	PlaneActor();
	~PlaneActor();
	vector<class BoxCollider*> GetBoxs() { return mBoxs; }
private:
	//AABBのコライダー
	vector<class BoxCollider*> mBoxs;

	class MeshRenderer* mMeshComp;
};