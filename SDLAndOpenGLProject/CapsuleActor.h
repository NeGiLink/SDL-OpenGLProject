#pragma once
#include "Actor.h"
#include "MeshRenderer.h"
#include "CapsuleCollider.h"
#include "Mesh.h"

//カプセル型のオブジェクト
//Unityのようにデフォルトで作成可能オブジェクト
class CapsuleActor : public ActorObject
{
public:
	CapsuleActor();

	void UpdateActor(float deltaTime) override;

	class CapsuleCollider* GetCapsule() { return mCapsule; }

	void OnCollisionEnter(class ActorObject* target) override;
private:
	//カプセルコライダー
	class CapsuleCollider* mCapsule;
};