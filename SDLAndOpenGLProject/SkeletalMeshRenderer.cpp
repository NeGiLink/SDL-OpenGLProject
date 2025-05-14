#include "SkeletalMeshRenderer.h"


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
				shader->SetMatrixUniforms("uMatrixPalette", &mAnimator->GetPalette().mEntry[0],
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
	if (!mAnimator) { return; }
	mAnimator->Update(deltaTime);
}
void SkeletalMeshRenderer::LoadSkeletonMesh(const string& fileName, ActorObject* actor)
{
	const vector<class Mesh*>& mesh = mGame->GetWinMain()->GetRenderer()->GetMeshs(fileName);
	mMeshs.insert(mMeshs.end(), mesh.begin(), mesh.end());

	Skeleton* sk = mGame->GetSkeleton(fileName);
	mSkeleton = sk;
	mSkeleton->SetParentActor(actor);
}