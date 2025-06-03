#include "SkeletonMeshActor.h"

SkeletonMeshActor::SkeletonMeshActor()
	: ActorObject()
	, mSkeletonMesh(nullptr)
	, mAnimator(nullptr)
{
	mSkeletonMesh = new SkeletalMeshRenderer(this);
	mAnimator = new Animator();

	mSkeletonMesh->SetAnimator(mAnimator);

}

void SkeletonMeshActor::Load(string filePath)
{
	mSkeletonMesh->LoadSkeletonMesh(filePath, this);

	mAnimator->SetSkeleton(mSkeletonMesh->GetSkeleton());
}

void SkeletonMeshActor::SetAnimatorName(string name)
{
	mAnimatorName = name;
	GetGame()->GetAnimator(mAnimatorName, mAnimator);
}
