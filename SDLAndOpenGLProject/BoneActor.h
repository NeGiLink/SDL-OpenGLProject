#pragma once
#include "Actor.h"

//�X�P���^�����b�V���̃{�[��1��1�̏����Ǘ�����BoneActor
//��Ɏq�I�u�W�F�N�g�̈ʒu�Ǘ����s���Ă��܂��B
class BoneActor : public ActorObject
{
public:
	void			ComputeWorldTransform(const class Matrix4* parentMatrix)override;

	void			SetBoneName(string name) { boneName = name; }

	void			SetBoneIndex(int index) { boneIndex = index; }

	void			SetBoneMatrix(Matrix4 mat) { mBoneMatrix = mat; }

	void			SetParentActor(ActorObject* actor) { parentActor = actor; }
private:
	string			boneName;

	int				boneIndex;

	Matrix4			mBoneMatrix;

	ActorObject*	parentActor;
};

