#include "Image.h"
#include "Texture.h"
#include "Shader.h"
#include "WinMain.h"
#include "BaseScene.h"
#include "Renderer.h"

Image::Image(BaseScene* game)
	:mGame(game)
	,mTexture(nullptr)
{
	//BaseScene‚É‘—‚éˆ—
	mGame->PushImage(this);
}

Image::~Image()
{
}

void Image::Load(std::string file)
{
	mTexture = mGame->GetWinMain()->GetRenderer()->GetTexture(file);
}

void Image::SetPosition(Vector2 pos)
{
	mTexturePos = pos;
}

void Image::Update(float deltaTime)
{
}

void Image::Draw(Shader* shader)
{
	// Draw title (if exists)
	if (mTexture)
	{
		DrawTexture(shader, mTexture, mTexturePos);
	}
}

void Image::Close()
{
	mState = EClosing;
}

void Image::DrawTexture(Shader* shader, Texture* texture, const Vector2& offset, float scale)
{
	// Scale the quad by the width/height of texture
	Matrix4 scaleMat = Matrix4::CreateScale(
		static_cast<float>(texture->GetWidth()) * scale,
		static_cast<float>(texture->GetHeight()) * scale,
		1.0f);
	// Translate to position on screen
	Matrix4 transMat = Matrix4::CreateTranslation(
		Vector3(offset.x, offset.y, 0.0f));
	// Set world transform
	Matrix4 world = scaleMat * transMat;
	shader->SetMatrixUniform("uWorldTransform", world);
	// Set current texture
	texture->SetActive();
	// Draw quad
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}
