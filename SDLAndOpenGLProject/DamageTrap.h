#pragma once
#include "Actor.h"
#include "MeshRenderer.h"
#include "BoxCollider.h"
#include "Mesh.h"

//テスト用のダメージオブジェクト
//プレイヤーがこのオブジェクトに当たった時にダメージを与えるためのもの
class DamageTrap : public ActorObject
{
public:
	DamageTrap();

	vector<class BoxCollider*>		GetBoxs() { return mBoxs; }
private:
	vector<class BoxCollider*>		mBoxs;
};

