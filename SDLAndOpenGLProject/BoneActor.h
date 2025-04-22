#pragma once
#include "Actor.h"

class BoneActor : public ActorObject
{
public:
	void ComputeWorldTransform(const class Matrix4* parentMatrix)override;

	void SetBoneIndex(int index) { boneIndex = index; }

	void SetBoneMatrix(Matrix4 mat) { mBoneMatrix = mat; }
private:
	int boneIndex;

	Matrix4 mBoneMatrix;
};

