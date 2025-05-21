#include "Text.h"

Text::Text(Font* font, const Vector2& pos, bool active)
: Image()
, mFont(font)
, mHighlighted(false)
{
	mTexture = nullptr;
	mTexturePos = pos;
	mFontSize = 30;
	mColor = Color::White;
}

Text::~Text()
{

}

void Text::SetText(const string& name)
{
	mName = name;

	if (mTexture)
	{
		mTexture->Unload();
		delete mTexture;
		mTexture = nullptr;
	}
	mTexture = mFont->RenderFreeText(mName,mColor,mFontSize);
	mTextureRect.x = 0;
	mTextureRect.y = 0;
	mTextureRect.w = static_cast<float>(mTexture->GetWidth());
	mTextureRect.h = static_cast<float>(mTexture->GetHeight());
}

void Text::SetFontSize(int size)
{
	mFontSize = size;
}

void Text::SetColor(Vector3 color)
{
	mColor = color;
}
