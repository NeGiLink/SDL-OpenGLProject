#pragma once
#include "Actor.h"
#include "MeshRenderer.h"
#include "SplineCamera.h"
#include "MoveComponent.h"
//スプラインカメラに使うオブジェクトクラス
//現在は未使用ですが今後使えるようにするためにおいています。
class SplineActor : public ActorObject
{
public:
	SplineActor();

	void ActorInput(const struct InputState& keys) override;

	void RestartSpline();
private:
	class SplineCamera* mCameraComp;
};

