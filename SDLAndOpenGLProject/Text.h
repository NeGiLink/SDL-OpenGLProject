#pragma once
#include "Image.h"
#include "Font.h"

class Text : public Image
{
private:
	string			mName;

	std::u8string   mU8Name;
	
	class Font*		mFont;
	
	Vector2			mDimensions;

	bool			mHighlighted;

	int				mFontSize;

	Vector3			mColor;
public:
					Text(class Font* font,const Vector2& pos,bool active = true);
					~Text();

	// Set the name of the button
	void			SetText(const string& name);

	void			SetFontSize(int size);

	void			SetColor(Vector3 color);


	class Font*		GetFont()const { return mFont; }
};