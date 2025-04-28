#pragma once
#include "Actor.h"
#include "MeshRenderer.h"
#include "SphereCollider.h"
#include "Mesh.h"

//球型のオブジェクト
//Unityのようにデフォルトで作成可能オブジェクト
class SphereActor : public ActorObject
{
public:
	SphereActor();

	void UpdateActor(float deltaTime) override;

	class SphereCollider* GetSphere() { return mSphere; }

	void OnCollisionEnter(class ActorObject* target) override;
private:
	//球のコライダー
	class SphereCollider* mSphere;
};

