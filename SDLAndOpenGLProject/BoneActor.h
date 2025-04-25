#pragma once
#include "Actor.h"

class BoneActor : public ActorObject
{
public:
	void ComputeWorldTransform(const class Matrix4* parentMatrix)override;

	void SetBoneName(std::string name) { boneName = name; }

	void SetBoneIndex(int index) { boneIndex = index; }

	void SetBoneMatrix(Matrix4 mat) { mBoneMatrix = mat; }

	void SetParentActor(ActorObject* actor) { parentActor = actor; }
private:
	std::string boneName;

	int boneIndex;

	Matrix4 mBoneMatrix;

	ActorObject* parentActor;
};

