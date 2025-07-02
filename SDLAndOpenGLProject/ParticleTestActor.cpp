#include "ParticleTestActor.h"

ParticleTestActor::ParticleTestActor()
	:ActorObject()
{
	mParticleSystem = new ParticleSystem(this);
	mParticleSystem->SetLoop(true);
	mParticleSystem->SetVisible(true);


	mParticleSystem->SetParticleLifeTime(1.0f);
}

ParticleTestActor::~ParticleTestActor()
{
}
