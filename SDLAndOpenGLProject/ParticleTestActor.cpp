#include "ParticleTestActor.h"

ParticleTestActor::ParticleTestActor()
	:ActorObject()
{
	mParticleSystem = new ParticleSystem(this);
	mParticleSystem->SetLoop(true);
	mParticleSystem->SetVisible(true);

	mParticleSystem->Emit(Vector3(0.0f, 0.0f, 0.0f),0);

	SetLocalPosition(Vector3(0.0f, 0.0f, 2.0f));
}

ParticleTestActor::~ParticleTestActor()
{
}
