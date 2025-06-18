#pragma once
#include "Actor.h"
#include "MeshRenderer.h"
#include "BoxCollider.h"
#include "PushButtonMove.h"
#include "Mesh.h"

/*
* ===�G���W����������/Engine internal processing===
*/

//���^�̃I�u�W�F�N�g
//Unity�̂悤�Ƀf�t�H���g�ō쐬�\�I�u�W�F�N�g
class CubeActor : public ActorObject
{
private:
	//AABB�̃R���C�_�[
	BoxCollider*	mBox;
public:
					CubeActor();

	BoxCollider*	GetBoxs() { return mBox; }

};

