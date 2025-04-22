#include "PointLightComponent.h"
#include "Shader.h"
#include "WinMain.h"
#include "BaseScene.h"
#include "Renderer.h"
#include "Mesh.h"
#include "VertexArray.h"
#include "Actor.h"

PointLightComponent::PointLightComponent(ActorObject* owner)
	:Component(owner)
{
	owner->GetGame()->GetWinMain()->GetRenderer()->AddPointLight(this);
}

PointLightComponent::~PointLightComponent()
{
	GetOwner()->GetGame()->GetWinMain()->GetRenderer()->RemovePointLight(this);
}

void PointLightComponent::Draw(Shader* shader, Mesh* mesh)
{
	for (unsigned int i = 0; i < mesh->GetVertexArrays().size(); i++) {
		// ���̊֐��ɓ���ɂ�����A�V�F�[�_�[���A�N�e�B�u�ł���A
		// �����b�V�����A�N�e�B�u�ł���Ɖ��肵�܂��B
		// ���[���h�ϊ��͊O���a�ɃX�P�[�����O����
		// �i���b�V�����a�Ŋ��������́j�A���[���h�ʒu�ɔz�u����܂��B
		Matrix4 scale = Matrix4::CreateScale(mOwner->GetLocalScale() * mOuterRadius / mesh->GetRadiusArray()[i]);
		Matrix4 trans = Matrix4::CreateTranslation(mOwner->GetLocalPosition());
		Matrix4 worldTransform = scale * trans;
		shader->SetMatrixUniform("uWorldTransform", worldTransform);
		//�|�C���g���C�g�V�F�[�_�[�萔��ݒ肷��
		shader->SetVectorUniform("uPointLight.mWorldPos", mOwner->GetLocalPosition());
		shader->SetVectorUniform("uPointLight.mDiffuseColor", mDiffuseColor);
		shader->SetFloatUniform("uPointLight.mInnerRadius", mInnerRadius);
		shader->SetFloatUniform("uPointLight.mOuterRadius", mOuterRadius);

		// ����`��
		glDrawElements(GL_TRIANGLES, mesh->GetVertexArrays()[i]->GetNumIndices(),
			GL_UNSIGNED_INT, nullptr);
	}
}