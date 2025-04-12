#pragma once
#include "Actor.h"
//�X�v���C���J�����Ɏg���I�u�W�F�N�g�N���X
//���݂͖��g�p�ł�������g����悤�ɂ��邽�߂ɂ����Ă��܂��B
class SplineActor : public ActorObject
{
public:
	SplineActor(class BaseScene* game);

	void ActorInput(const bool* keys) override;

	void RestartSpline();
private:
	class SplineCamera* mCameraComp;
};

