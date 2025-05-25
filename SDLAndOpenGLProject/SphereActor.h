#pragma once
#include "Actor.h"
#include "MeshRenderer.h"
#include "SphereCollider.h"
#include "Mesh.h"

//球型のオブジェクト
//Unityのようにデフォルトで作成可能オブジェクト
class SphereActor : public ActorObject
{
private:
	//球のコライダー
	class SphereCollider*	mSphere;
public:
							SphereActor();

	class SphereCollider*	GetSphere() { return mSphere; }
};

