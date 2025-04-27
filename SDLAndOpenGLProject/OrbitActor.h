#pragma once
#include "Actor.h"
#include "MeshRenderer.h"
#include "OrbitCamera.h"
#include "MoveComponent.h"

//軌道カメラに使うオブジェクトのクラス
//今後使うため残しています。
class OrbitActor : public ActorObject
{
public:
	OrbitActor();

	void ActorInput(const struct InputState& keys) override;

	void SetVisible(bool visible);
private:
	class OrbitCamera*		mCameraComp;

	class MeshRenderer*		mMeshComp;
};

