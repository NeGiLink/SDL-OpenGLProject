#pragma once
#include "Actor.h"
#include "MeshRenderer.h"
#include "OrbitCamera.h"
#include "MoveComponent.h"

/*
* ===�G���W����������/Engine internal processing===
*/

//���Е���
//�O���J�����Ɏg���I�u�W�F�N�g�̃N���X
//����g�����ߎc���Ă��܂��B
class OrbitActor : public ActorObject
{
private:
	class OrbitCamera*		mCameraComp;

	class MeshRenderer*		mMeshComp;
public:
							OrbitActor();

	void					ActorInput(const struct InputState& keys) override;

	void					SetVisible(bool visible);
};

