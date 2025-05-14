#pragma once
#include "Actor.h"
#include "MeshRenderer.h"
#include "SphereCollider.h"
#include "Mesh.h"

//���^�̃I�u�W�F�N�g
//Unity�̂悤�Ƀf�t�H���g�ō쐬�\�I�u�W�F�N�g
class SphereActor : public ActorObject
{
public:
							SphereActor();

	class SphereCollider*	GetSphere() { return mSphere; }
private:
	//���̃R���C�_�[
	class SphereCollider*	mSphere;
};

