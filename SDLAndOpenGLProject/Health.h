#pragma once
#include "Actor.h"
#include "MeshRenderer.h"
#include "BoxCollider.h"
#include "Mesh.h"

//機能テスト用のオブジェクト
//プレイヤーのHPを回復させるためのオブジェクト
class HealthObject : public ActorObject
{
public:
									HealthObject();

	void							UpdateActor(float deltaTime)override;

	vector<class BoxCollider*>		GetBoxs() { return mBoxs; }
private:
	vector<class BoxCollider*>		mBoxs;
};

