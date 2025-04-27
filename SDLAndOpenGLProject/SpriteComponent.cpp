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
		// テクスチャの幅/高さでクアッドをスケールします
		Matrix4 scaleMat = Matrix4::CreateScale(
			static_cast<float>(mTexWidth),
			static_cast<float>(mTexHeight),
			1.0f);

		Matrix4 world = scaleMat * mOwner->GetWorldTransform();

		// すべてのスプライトが同じシェーダー/頂点を使用しているため、
		// ゲームは最初にどのスプライトを描画する前にそれらをアクティブに設定します。

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