#include "MeshRenderer.h"


MeshRenderer::MeshRenderer(ActorObject* owner, bool isSkeletal)
	:Component(owner)
	, mTextureIndex(0)
	, mVisible(true)
	, mIsSkeletal(isSkeletal)
{
	owner->GetGame()->GetWinMain()->GetRenderer()->AddMeshComp(this);
}

MeshRenderer::~MeshRenderer()
{
	GetOwner()->GetGame()->GetWinMain()->GetRenderer()->RemoveMeshComp(this);
}

void MeshRenderer::Draw(Shader* shader)
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
				shader->SetColorUniform("uTexture",m);
				// メッシュの頂点配列をアクティブに設定します
				VertexArray* va = mMeshs[i]->GetVertexArrays()[j];
				va->SetActive();
				// 描画
				glDrawElements(GL_TRIANGLES, va->GetNumIndices(), GL_UNSIGNED_INT, nullptr);
			}
		}
	}
}