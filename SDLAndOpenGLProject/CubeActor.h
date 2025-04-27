#pragma once
#include "Actor.h"
#include "MeshRenderer.h"
#include "BoxCollider.h"
#include "Mesh.h"

class CubeActor : public ActorObject
{
public:
	CubeActor();

	std::vector<class BoxCollider*> GetBoxs() { return mBoxs; }

	void UpdateActor(float deltaTime) override;

	void ActorInput(const struct InputState& keys) override;

	void OnCollisionEnter(class ActorObject* target) override;
private:
	std::vector<class BoxCollider*> mBoxs;
};

