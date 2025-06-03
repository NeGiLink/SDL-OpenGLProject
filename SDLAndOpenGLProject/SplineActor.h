#pragma once
#include "Actor.h"
#include "MeshRenderer.h"
#include "SplineCamera.h"
#include "MoveComponent.h"

//���Е���
//�X�v���C���J�����Ɏg���I�u�W�F�N�g�N���X
//���݂͖��g�p�ł�������g����悤�ɂ��邽�߂ɂ����Ă��܂��B
class SplineActor : public ActorObject
{
private:
	class SplineCamera*		mCameraComp;
public:
							SplineActor();

	void					ActorInput(const struct InputState& keys) override;

	void					RestartSpline();
};

