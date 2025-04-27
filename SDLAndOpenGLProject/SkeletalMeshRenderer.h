#pragma once
#include "MeshRenderer.h"
#include "MatrixPalette.h"
#include "Animation.h"
#include "Skeleton.h"
#include "Shader.h"
#include "Mesh.h"
#include "Actor.h"
#include "Texture.h"
#include "VertexArray.h"
#include "Animator.h"

class SkeletalMeshRenderer : public MeshRenderer
{
public:
	SkeletalMeshRenderer(class ActorObject* owner);
	// スケルタルモデルの描画
	void Draw(class Shader* shader) override;

	void Update(float deltaTime) override;

	// Setters
	void SetSkeleton(class Skeleton* sk, class ActorObject* actor) 
	{
		mSkeleton = sk; 
		mSkeleton->SetParentActor(actor);
	}

	void SetAnimator(class Animator* animator) { mAnimator = animator; }

	class Skeleton* GetSkeleton() { return mSkeleton; }

protected:

	class Animator*					mAnimator;

	class Skeleton*					mSkeleton;
};