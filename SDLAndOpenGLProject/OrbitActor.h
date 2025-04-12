#pragma once
#include "Actor.h"

//�O���J�����Ɏg���I�u�W�F�N�g�̃N���X
//����g�����ߎc���Ă��܂��B
class OrbitActor : public ActorObject
{
public:
	OrbitActor(class BaseScene* game);

	void ActorInput(const bool* keys) override;

	void SetVisible(bool visible);
private:
	class OrbitCamera*		mCameraComp;

	class MeshRenderer*		mMeshComp;
};

