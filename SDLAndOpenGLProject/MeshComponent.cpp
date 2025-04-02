#include "MeshComponent.h"
#include "Shader.h"
#include "Mesh.h"
#include "Actor.h"
#include "WinMain.h"
#include "Renderer.h"
#include "Texture.h"
#include "VertexArray.h"

MeshComponent::MeshComponent(ActorObject* owner, bool isSkeletal)
	:Component(owner)
	, mTextureIndex(0)
	, mVisible(true)
	, mIsSkeletal(isSkeletal)
{
	mOwner->GetGame()->GetRenderer()->AddMeshComp(this);
}

MeshComponent::~MeshComponent()
{
	mOwner->GetGame()->GetRenderer()->RemoveMeshComp(this);
}

void MeshComponent::Draw(Shader* shader)
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
				shader->SetFloatUniform("uSpecPower", mMeshs[i]->GetSpecPowers()[j]);
				Texture* t = nullptr;
				if (mMeshs[i]->IsRenderType()[j] == Mesh::RenderType::Tex) {
					// Set the active texture
					t = mMeshs[i]->GetTexture(j);
					if (t)
					{
						t->SetActive();
					}
				}
				else if(mMeshs[i]->IsRenderType()[j] == Mesh::RenderType::Mat)
				{
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
				}
				// Set the mesh's vertex array as active
				VertexArray* va = mMeshs[i]->GetVertexArrays()[j];
				va->SetActive();
				// Draw
				glDrawElements(GL_TRIANGLES, va->GetNumIndices(), GL_UNSIGNED_INT, nullptr);
			}
		}
	}
}