#include "Image.h"


Image::Image(bool active)
	:mGame(GameApp::GetActiveScene())
	,mTexture(nullptr)
{
	updateTogether = active;
	mTexScale = Vector3(1.0f, 1.0f, 1.0f);
	if (updateTogether) {
		//BaseScene‚É‘—‚éˆ—
		mGame->PushImage(this);
	}
}

Image::~Image()
{
}

void Image::Load(std::string file)
{
	mTexture = mGame->GetWinMain()->GetRenderer()->GetTexture(file);
}

void Image::SetTexture(Texture* texture)
{
	mTexture = texture;
}

void Image::SetPosition(Vector2 pos)
{
	mTexturePos = pos;
}

void Image::SetScale(Vector3 scale)
{
	mTexScale = scale;
}

void Image::SetAngleZ(float angle)
{
	mAngleZ = angle;
}

void Image::Update(float deltaTime)
{
}

void Image::Draw(Shader* shader)
{
	// Draw title (if exists)
	if (mTexture)
	{
		DrawTexture(shader, mTexture, mTexturePos,mTexScale,mAngleZ);
	}
}

void Image::UnLoad()
{
	if (mTexture) {
		mTexture->Unload();
		delete mTexture;
	}
}

void Image::Close()
{
	mState = EClosing;
}

void Image::Active()
{
	mState = EActive;
}

void Image::DrawTexture(Shader* shader, Texture* texture, const Vector2& offset, Vector3 scale,float angle)
{
	// Scale the quad by the width/height of texture
	Matrix4 scaleMat = Matrix4::CreateScale(
		static_cast<float>(texture->GetWidth()) * scale.x,
		static_cast<float>(texture->GetHeight()) * scale.y,
		scale.z);

	// ‰ñ“]iZŽ²‰ñ“]j
	Matrix4 rotationMat = Matrix4::CreateRotationZ(angle);

	// Translate to position on screen
	Matrix4 transMat = Matrix4::CreateTranslation(
		Vector3(offset.x, offset.y, 0.0f));

	// Set world transform
	Matrix4 world = scaleMat * rotationMat * transMat;
	shader->SetMatrixUniform("uWorldTransform", world);
	// Set current texture
	texture->SetActive();
	// Draw quad
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}
