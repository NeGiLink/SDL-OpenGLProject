#pragma once
#include "Actor.h"
#include "MeshRenderer.h"
#include "BoxCollider.h"
#include "Mesh.h"

//機能テスト用のオブジェクト
//プレイヤーのHPを回復させるためのオブジェクト
class HealthObject : public ActorObject
{
private:
	vector<class BoxCollider*>		mBoxs;
public:
									HealthObject();

	void							UpdateActor(float deltaTime)override;

	vector<class BoxCollider*>		GetBoxs() { return mBoxs; }
};

