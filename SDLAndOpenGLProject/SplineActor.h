#pragma once
#include "Actor.h"
//スプラインカメラに使うオブジェクトクラス
//現在は未使用ですが今後使えるようにするためにおいています。
class SplineActor : public ActorObject
{
public:
	SplineActor(class BaseScene* game);

	void ActorInput(const bool* keys) override;

	void RestartSpline();
private:
	class SplineCamera* mCameraComp;
};

