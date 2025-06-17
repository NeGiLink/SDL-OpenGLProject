#pragma once
#include "MeshActor.h"
#include "TargetActor.h"

class Stages00 : public ActorObject
{
private:
	MeshActor* mDebugStage;

	MeshActor* mDebugStage2;

	MeshActor* mDebugStage3;

	MeshActor* mDebugStage4;

	MeshActor* mFloor00;

	MeshActor* mWall00;

	MeshActor* mWall01;
	
	MeshActor* mWall02;

	TargetActor* mTarget1;
	TargetActor* mTarget2;
	TargetActor* mTarget3;
public:
	Stages00();

	void					Initialize();

	void					UpdateActor(float deltaTime) override;
};

