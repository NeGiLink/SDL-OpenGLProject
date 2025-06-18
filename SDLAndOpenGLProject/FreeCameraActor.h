#pragma once
#include "Actor.h"
#include "MeshRenderer.h"
#include "FreeCamera.h"

/*
* ===�G���W����������/Engine internal processing===
*/

// �t���[�J�������g�p���邽�߂̃A�N�^�[
// Unity�̂悤�Ƀf�t�H���g�ō쐬�\�I�u�W�F�N�g
class FreeCameraActor : public ActorObject
{
private:
	class FreeCamera*	mCameraComp;
public:
						FreeCameraActor();

	class FreeCamera*	GetCamera() { return mCameraComp; }
};

