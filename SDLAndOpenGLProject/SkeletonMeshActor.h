#pragma once
#include "Actor.h"
#include "Mesh.h"
#include "SkeletalMeshRenderer.h"
#include "Animator.h"
#include "BoxCollider.h"

/*
* ===�G���W����������/Engine internal processing===
*/

//3D���f����ǂݍ��ރN���X
//�X�P���g���L���3D���f����
//�ǂݍ��݂����̃N���X
//ActorObject���p�����Ă���̂�1�I�u�W�F�N�g�Ƃ��ăJ�E���g
class SkeletonMeshActor : public ActorObject
{
private:
	class SkeletalMeshRenderer* mSkeletonMesh;

	class Animator*				mAnimator;

	string						mAnimatorName;
public:
	SkeletonMeshActor();

	void Load(string filePath);

	class SkeletalMeshRenderer* GetSkeletalMeshRenderer() { return mSkeletonMesh; }

	class Animator* GetAnimator() { return mAnimator; }

	void SetAnimatorName(string name);
};

