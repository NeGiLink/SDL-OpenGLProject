#include "SkeletalMeshRenderer.h"
#include "Shader.h"
#include "Mesh.h"
#include "Actor.h"
#include "WinMain.h"
#include "Renderer.h"
#include "Texture.h"
#include "VertexArray.h"
#include "Animation.h"

SkeletalMeshRenderer::SkeletalMeshRenderer(ActorObject* owner)
	:MeshRenderer(owner, true)
	, mSkeleton(nullptr)
{
}

void SkeletalMeshRenderer::Draw(Shader* shader)
{
	for (unsigned int i = 0; i < mMeshs.size(); i++) 
	{
		for (unsigned int j = 0; j < mMeshs[i]->GetVertexArrays().size(); j++) 
		{
			if (mMeshs[i])
			{
				// Set the world transform
				shader->SetMatrixUniform("uWorldTransform",
					mOwner->GetWorldTransform());
				// Set the matrix palette
				shader->SetMatrixUniforms("uMatrixPalette", &mPalette.mEntry[0],
					MAX_SKELETON_BONES);
				// Set specular power
				shader->SetFloatUniform("uSpecPower", mMeshs[i]->GetMaterialInfo()[j].Shininess);
				Texture* t = nullptr;
				// Set the active texture
				t = mMeshs[i]->GetTexture(j);
				if (t)
				{
					t->SetActive();
				}
				else {
					shader->SetNoTexture();
				}
				MaterialInfo m = mMeshs[i]->GetMaterialInfo()[j];
				shader->SetColorUniform("uTexture", m);
				// メッシュの頂点配列をアクティブに設定します
				VertexArray* va = mMeshs[i]->GetVertexArrays()[j];
				va->SetActive();
				// 描画
				glDrawElements(GL_TRIANGLES, va->GetNumIndices(), GL_UNSIGNED_INT, nullptr);
			}
		}
	}
}

void SkeletalMeshRenderer::Update(float deltaTime)
{
	if (mAnimation && mSkeleton)
	{
		mAnimTime += deltaTime * mAnimPlayRate;
		if (mAnimation->IsLoop()) 
		{
			if (mAnimTime > mAnimation->GetDuration()) 
			{
				mAnimTime = 0.0f;
			}
		}
		else
		{
			if (mAnimTime > mAnimation->GetDuration())
			{
				mAnimTime = mAnimation->GetDuration();
				if(!mAnimation->IsAnimationEnd())
				{
					mAnimation->SetIsAnimationEnd(true);
				}
			}
		}
		// Recompute matrix palette
		ComputeMatrixPalette();
	}

	if (blending)
	{
		mBlendAnimTime += deltaTime * mAnimPlayRate;

		float t = Math::Clamp(mBlendAnimTime / mBlendElapsed, 0.0f, 1.0f);

		BlendComputeMatrixPalette();

		if (t >= mBlendElapsed)
		{
			mAnimTime = mBlendAnimTime;
			mAnimation = mBlendAnimation;
			mBlendAnimation = nullptr;
			blending = false;
		}
	}
}

float SkeletalMeshRenderer::PlayAnimation(Animation* anim, float playRate)
{
	if (mAnimation == anim) { return 0.0f; }
	mAnimation = anim;
	mAnimTime = 0.0f;
	mAnimPlayRate = playRate;

	mAnimation->SetIsAnimationEnd(false);

	if (!mAnimation) { return 0.0f; }

	ComputeMatrixPalette();

	return mAnimation->GetDuration();
}

float SkeletalMeshRenderer::PlayBlendAnimation(Animation* anim, float playRate, float blendTime)
{
	if (mAnimation == anim||mBlendAnimation == anim ) { return 0.0f; }

	mBlendAnimation = anim;
	mBlendElapsed = blendTime;
	mAnimPlayRate = playRate;
	mBlendAnimTime = 0.0f;

	mBlendAnimation->SetIsAnimationEnd(false);
	mAnimation->SetIsAnimationEnd(false);
	blending = true;

	return mAnimation->GetDuration();
}

void SkeletalMeshRenderer::ComputeMatrixPalette()
{
	const std::vector<Matrix4>& globalInvBindPoses = mSkeleton->GetGlobalInvBindPoses();
	std::vector<Matrix4> currentPoses;
	mAnimation->GetGlobalPoseAtTime(currentPoses, mSkeleton, mAnimTime);
	mSkeleton->SetGlobalCurrentPoses(currentPoses);
	// Setup the palette for each bone
	for (size_t i = 0; i < mSkeleton->GetNumBones(); i++)
	{
		// Global inverse bind pose matrix times current pose matrix
		mPalette.mEntry[i] = globalInvBindPoses[i] * currentPoses[i];
		mSkeleton->GetBoneActor()[i]->SetScale(currentPoses[i].GetScale());
		mSkeleton->GetBoneActor()[i]->SetRotation(currentPoses[i].GetRotation());
		mSkeleton->GetBoneActor()[i]->SetPosition(currentPoses[i].GetTranslation());
	}
}

void SkeletalMeshRenderer::BlendComputeMatrixPalette()
{
	const std::vector<Matrix4>& globalInvBindPoses = mSkeleton->GetGlobalInvBindPoses();
	std::vector<Matrix4> nowPose;
	std::vector<Matrix4> nextPose;
	std::vector<Matrix4> goalPose;

	// 経過時間に対する補間率
	float t = Math::Clamp(mBlendAnimTime / mBlendElapsed, 0.0f, 1.0f);

	// アニメーションタイムを使ってそれぞれのポーズを取得
	mAnimation->GetGlobalPoseAtTime(nowPose, mSkeleton, mAnimTime);
	// 進行具合に応じて取得
	mBlendAnimation->GetGlobalPoseAtTime(nextPose, mSkeleton,mBlendAnimTime);

	if (nowPose.size() != nextPose.size()) 
	{
		int a = nowPose.size();
		int b = nextPose.size();
	}

	goalPose.resize(nowPose.size());

	for (size_t i = 0; i < nowPose.size(); i++)
	{
		// BoneTransformに変換して補間（Lerp/Slerp）
		BoneTransform transformA, transformB;
		transformA.FromMatrix(nowPose[i]);
		transformB.FromMatrix(nextPose[i]);

		BoneTransform blended = BoneTransform::Interpolate(transformA,transformB,t);

		goalPose[i] = blended.ToMatrix();
		mSkeleton->GetBoneActor()[i]->SetBoneMatrix(goalPose[i]);
	}

	mSkeleton->SetGlobalCurrentPoses(goalPose);

	for (size_t i = 0; i < mSkeleton->GetNumBones(); i++)
	{
		if (mSkeleton->GetBoneActor()[i]->GetBoneName() == "RightHand") 
		{
			int i = 0;
		}
		mPalette.mEntry[i] = globalInvBindPoses[i] * goalPose[i];
		mSkeleton->GetBoneActor()[i]->SetScale(goalPose[i].GetScale());
		mSkeleton->GetBoneActor()[i]->SetRotation(goalPose[i].GetRotation());
		mSkeleton->GetBoneActor()[i]->SetPosition(goalPose[i].GetTranslation());
	}
}
