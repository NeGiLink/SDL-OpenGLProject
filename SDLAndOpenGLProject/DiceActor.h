#pragma once
#include "Actor.h"

//モデルをテスト読み込みしているクラス
class DiceActor : public ActorObject
{
public:
	DiceActor(class BaseScene* game);

	std::vector<class BoxCollider*> GetBoxs() { return mBoxs; }

	void OnCollisionEnter(class ActorObject* target) override;
private:
	std::vector<class BoxCollider*> mBoxs;
};

