#pragma once
#include "Actor.h"
#include "MeshActor.h"
#include "BulletActor.h"

class GunActor : public ActorObject
{
private:
	MeshActor*				mGunMesh;

public:
							GunActor();

	void					FixedUpdateActor(float deltaTime)override;

	void					UpdateActor(float deltaTime) override;

	void					ActorInput(const struct InputState& keys) override;

	void					Fire();
};

