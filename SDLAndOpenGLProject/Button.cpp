#include "Button.h"
Button::Button(const string& name, Font* font,
	std::function<void()> onClick,
	const Vector2& pos, const Vector2& dims)

	: Image()
	, mOnClick(onClick)
	, mNameTex(nullptr)
	, mFont(font)
	, mPosition(pos)
	, mDimensions(dims)
	, mHighlighted(false)
{
	SetName(name);
}

Button::~Button()
{
	mGame->RemoveImage(this);
}

void Button::SetName(const string& name)
{
	mName = name;

	if (mNameTex)
	{
		mNameTex->Unload();
		delete mNameTex;
		mNameTex = nullptr;
	}
	mNameTex = mFont->RenderText(mName);
}

bool Button::ContainsPoint(const Vector2& pt) const
{
	bool no = pt.x < (mPosition.x - mDimensions.x / 2.0f) ||
		pt.x >(mPosition.x + mDimensions.x / 2.0f) ||
		pt.y < (mPosition.y - mDimensions.y / 2.0f) ||
		pt.y >(mPosition.y + mDimensions.y / 2.0f);
	return !no;
}

void Button::OnClick()
{
	// Call attached handler, if it exists
	if (mOnClick)
	{
		mOnClick();
	}
}

void Button::Draw(Shader* shader)
{
	if (mButtonTex)
	{
		DrawTexture(shader, mButtonTex, mPosition);
	}
	if (mNameTex)
	{
		DrawTexture(shader, mNameTex, mPosition);
	}
}

void Button::DrawTexture(Shader* shader, Texture* texture, const Vector2& offset, Vector3 scale, float angle)
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
