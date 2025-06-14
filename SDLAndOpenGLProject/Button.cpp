#include "Button.h"
Button::Button(const string& name, Font* font,
	std::function<void()> onClick,
	const Vector2& pos, const Vector2& dims)

	: Image()
	, mOnClick(onClick)
	, mFont(font)
	, mPosition(pos)
	, mDimensions(dims)
	, mHighlighted(false)
{
	mButtonImage = new Image();
	mButtonImage->SetPosition(pos);

	mNameText = new Text(mFont,mPosition);
	mNameText->SetText(name);
}

Button::~Button()
{
	//画像の解放
	//ボタン本体
	mGame->RemoveImage(this);
	//ボタンの枠
	mGame->RemoveImage(mButtonImage);
	//ボタンの文字
	mGame->RemoveImage(mNameText);
}

void Button::SetButtonText(Texture* texture)
{
	mButtonImage->SetTexture(texture);
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
	if (GameStateClass::mGameEventFrag) { return; }


	GameStateClass::mGameEventFrag = true;


	// Call attached handler, if it exists
	if (mOnClick)
	{
		GameStateClass::mGameEventFrag = false;
		mOnClick();
	}
}

void Button::DrawTexture(Shader* shader, Texture* texture, const Vector2& offset, Vector3 scale, float angle)
{
	// Scale the quad by the width/height of texture
	Matrix4 scaleMat = Matrix4::CreateScale(
		static_cast<float>(texture->GetWidth()) * scale.x,
		static_cast<float>(texture->GetHeight()) * scale.y,
		scale.z);
	// 回転（Z軸回転）
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
