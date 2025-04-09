#include "Text.h"
#include "Texture.h"
#include "Shader.h"
#include "WinMain.h"
#include "BaseScene.h"
#include "Renderer.h"
#include "Font.h"

Text::Text(class BaseScene* game, Font* font, const Vector2& pos)
: Image(game)
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

void Text::SetText(const std::string& name)
{
	mName = name;

	if (mTexture)
	{
		mTexture->Unload();
		delete mTexture;
		mTexture = nullptr;
	}
	mTexture = mFont->RenderFreeText(mName,mColor,mFontSize);
}

void Text::SetFontSize(int size)
{
	mFontSize = size;
}

void Text::SetColor(Vector3 color)
{
	mColor = color;
}
