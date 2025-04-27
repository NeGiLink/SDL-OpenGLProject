#pragma once
#include "Actor.h"
#include "MeshRenderer.h"
#include "SphereCollider.h"
#include "Mesh.h"

class SphereActor : public ActorObject
{
public:
	SphereActor();

	void UpdateActor(float deltaTime) override;

	class SphereCollider* GetSphere() { return mSphere; }

	void OnCollisionEnter(class ActorObject* target) override;
private:
	class SphereCollider* mSphere;
};

