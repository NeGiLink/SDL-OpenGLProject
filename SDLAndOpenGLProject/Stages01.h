#pragma once
#include "MeshActor.h"
#include "SkeletonMeshActor.h"
#include "CubeActor.h"

class Stages01 : public ActorObject
{
private:
	SkeletonMeshActor* mTestCharacter;

	SkeletonMeshActor* mSmallCharacter;

	MeshActor* mFloor00;

	MeshActor* mWall00;

	MeshActor* mWall01;

	MeshActor* mWall02;

	MeshActor* mWall03;

	CubeActor* mCubeActor00;

	CubeActor* mCubeActor01;
	
	CubeActor* mCubeActor02;
public:
	Stages01();

	void Initialize();

	void UpdateActor(float deltaTime)override;

	void ActorInput(const InputState& state)override;
};