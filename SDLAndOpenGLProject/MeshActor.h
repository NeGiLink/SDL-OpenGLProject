#pragma once
#include "Actor.h"
#include "MeshRenderer.h"
#include "BoxCollider.h"
#include "Mesh.h"

//3D���f����ǂݍ��ރN���X
//�X�P���g��������3D���f����
//�ǂݍ��݂����̃N���X
//ActorObject���p�����Ă���̂�1�I�u�W�F�N�g�Ƃ��ăJ�E���g
class MeshActor : public ActorObject
{
private:
	MeshRenderer*				mMeshRenderer;

	vector<class BoxCollider*>	mBoxs;
public:
	void Load(string filePath);

	void SetTrigger(bool active);
};

