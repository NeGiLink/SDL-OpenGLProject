#pragma once
#include "Actor.h"
#include "SoundEvent.h"

class FPSActor : public ActorObject
{
public:
	FPSActor(class WinMain* game);

	void UpdateActor(float deltaTime) override;
	void ActorInput(const bool* keys) override;

	void Shoot();

	void SetFootstepSurface(float value);

	void SetVisible(bool visible);

	void FixCollisions();
private:
	class MoveComponent* mMoveComp;
	class AudioComponent* mAudioComp;
	class MeshComponent* mMeshComp;
	class FPSCamera* mCameraComp;
	class BoxComponent* mBoxComp;
	SoundEvent mFootstep;
	float mLastFootstep;
};