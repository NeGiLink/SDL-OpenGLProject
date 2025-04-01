#include "PointLightComponent.h"
#include "Shader.h"
#include "WinMain.h"
#include "Renderer.h"
#include "Mesh.h"
#include "VertexArray.h"
#include "Actor.h"

PointLightComponent::PointLightComponent(ActorObject* owner)
	:Component(owner)
{
	owner->GetGame()->GetRenderer()->AddPointLight(this);
}

PointLightComponent::~PointLightComponent()
{
	mOwner->GetGame()->GetRenderer()->RemovePointLight(this);
}

void PointLightComponent::Draw(Shader* shader, Mesh* mesh)
{
	for (unsigned int i = 0; i < mesh->GetVertexArrays().size(); i++) {
		// We assume, coming into this function, that the shader is active
		// and the sphere mesh is active

		// World transform is scaled to the outer radius (divided by the mesh radius)
		// and positioned to the world position
		Matrix4 scale = Matrix4::CreateScale(mOwner->GetScale() *
			mOuterRadius / mesh->GetRadiusArray()[i]);
		Matrix4 trans = Matrix4::CreateTranslation(mOwner->GetPosition());
		Matrix4 worldTransform = scale * trans;
		shader->SetMatrixUniform("uWorldTransform", worldTransform);
		// Set point light shader constants
		shader->SetVectorUniform("uPointLight.mWorldPos", mOwner->GetPosition());
		shader->SetVectorUniform("uPointLight.mDiffuseColor", mDiffuseColor);
		shader->SetFloatUniform("uPointLight.mInnerRadius", mInnerRadius);
		shader->SetFloatUniform("uPointLight.mOuterRadius", mOuterRadius);

		// Draw the sphere
		glDrawElements(GL_TRIANGLES, mesh->GetVertexArrays()[i]->GetNumIndices(),
			GL_UNSIGNED_INT, nullptr);
	}
}