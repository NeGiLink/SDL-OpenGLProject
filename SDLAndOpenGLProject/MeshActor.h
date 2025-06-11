#pragma once
#include "Actor.h"
#include "MeshRenderer.h"
#include "BoxCollider.h"
#include "SphereCollider.h"
#include "CapsuleCollider.h"
#include "Mesh.h"

//3Dモデルを読み込むクラス
//スケルトン無しの3Dモデルを
//読み込みだけのクラス
//ActorObjectを継承しているので1オブジェクトとしてカウント
class MeshActor : public ActorObject
{
private:
	MeshRenderer*				mMeshRenderer;

	class BoxCollider*			mBoxCollider;

	class SphereCollider*		mSphereCollider;

	class CapsuleCollider*		mCapsuleCollider;

public:
	void Load(string filePath);

	void SetTrigger(bool active);

	void AddBoxCollider();

	void AddSphereCollider();

	void AddCapsuleCollider();

	class BoxCollider* GetBoxCollider() { return mBoxCollider; }

	class SphereCollider* GetSphereCollider() { return mSphereCollider; }

	class CapsuleCollider* GetCapsuleCollider() { return mCapsuleCollider; }
};

