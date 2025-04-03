#pragma once
#include "MeshRenderer.h"
#include "MatrixPalette.h"

class CharacterMeshRenderer : public MeshRenderer
{
public:
	CharacterMeshRenderer(class ActorObject* owner);

	void Draw(class Shader* shader) override;
	void Update(float deltaTime) override;
	// Setters
	void SetSkeleton(const class Skeleton* sk) { mSkeleton = sk; }

	// Play an animation. Returns the length of the animation
	float PlayAnimation(const class Animation* anim, float playRate = 1.0f);
protected:
	void ComputeMatrixPalette();

	MatrixPalette mPalette;
	const class Skeleton* mSkeleton;
	const class Animation* mAnimation;
	float mAnimPlayRate;
	float mAnimTime;
};

