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
				// Set the active texture
				Texture* t = mMeshs[i]->GetTexture(i);
				if (t)
				{
					t->SetActive();
				}
				if (mMeshs[i]->GetMaterialShader()) {
					mMeshs[i]->GetMaterialShader()->SetColorUniform("texture1");
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