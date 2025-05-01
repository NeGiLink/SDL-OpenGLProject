#pragma once
#include "Actor.h"
#include "MeshRenderer.h"
#include "BoxCollider.h"
#include "Mesh.h"

//���ʌ^�̃I�u�W�F�N�g
//Unity�̂悤�Ƀf�t�H���g�ō쐬�\�I�u�W�F�N�g
class PlaneActor : public ActorObject
{
public:
	PlaneActor();
	~PlaneActor();
	vector<class BoxCollider*> GetBoxs() { return mBoxs; }
private:
	//AABB�̃R���C�_�[
	vector<class BoxCollider*> mBoxs;

	class MeshRenderer* mMeshComp;
};