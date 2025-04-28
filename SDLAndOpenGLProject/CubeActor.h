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

	std::vector<class BoxCollider*> GetBoxs() { return mBoxs; }

	void ActorInput(const struct InputState& keys) override;

private:
	//AABBのコライダー
	std::vector<class BoxCollider*> mBoxs;
	//テストように用意した移動機能
	PushButtonMove* mPushButtonMove;
};

