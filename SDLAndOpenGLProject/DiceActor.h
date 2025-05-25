#pragma once
#include "Actor.h"
#include "MeshRenderer.h"
#include "BoxCollider.h"
#include "Mesh.h"

//モデルをテスト読み込みしているクラス
class DiceActor : public ActorObject
{
private:
	vector<class BoxCollider*>		mBoxs;

	Vector3							mPos;
public:
									DiceActor();

	vector<class BoxCollider*>		GetBoxs() { return mBoxs; }
};

