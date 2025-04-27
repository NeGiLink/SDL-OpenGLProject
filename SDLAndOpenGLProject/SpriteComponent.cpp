#include "SpriteComponent.h"


SpriteComponent::SpriteComponent(ActorObject* owner, int drawOrder)
	:Component(owner)
	, mTexture(nullptr)
	, mDrawOrder(drawOrder)
	, mTexWidth(0)
	, mTexHeight(0)
	, mVisible(true)
{
	owner->GetGame()->GetWinMain()->GetRenderer()->AddSprite(this);
}

SpriteComponent::~SpriteComponent()
{
	GetOwner()->GetGame()->GetWinMain()->GetRenderer()->RemoveSprite(this);
}

void SpriteComponent::Draw(Shader* shader)
{
	if (mTexture)
	{
		// �e�N�X�`���̕�/�����ŃN�A�b�h���X�P�[�����܂�
		Matrix4 scaleMat = Matrix4::CreateScale(
			static_cast<float>(mTexWidth),
			static_cast<float>(mTexHeight),
			1.0f);

		Matrix4 world = scaleMat * mOwner->GetWorldTransform();

		// ���ׂẴX�v���C�g�������V�F�[�_�[/���_���g�p���Ă��邽�߁A
		// �Q�[���͍ŏ��ɂǂ̃X�v���C�g��`�悷��O�ɂ������A�N�e�B�u�ɐݒ肵�܂��B

		// Set world transform
		shader->SetMatrixUniform("uWorldTransform", world);
		// Set current texture
		mTexture->SetActive();
		// Draw quad
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	}
}

void SpriteComponent::SetTexture(Texture* texture)
{
	mTexture = texture;
	// Set width/height
	mTexWidth = texture->GetWidth();
	mTexHeight = texture->GetHeight();
}