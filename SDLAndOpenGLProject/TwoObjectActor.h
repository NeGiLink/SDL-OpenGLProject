#pragma once
#include "Actor.h"

//FBXファイルに2つのモデルが一緒にあった時の
//読み込みを確認するためのクラス
class TwoObjectActor : public ActorObject
{
public:
	TwoObjectActor(class BaseScene* game);
	void UpdateActor(float deltaTime) override;
};

