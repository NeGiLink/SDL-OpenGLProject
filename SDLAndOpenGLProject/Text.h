#pragma once
#include "Image.h"
#include "Font.h"

class Text : public Image
{
private:
	string			mName;

	ccp_String      mText;
	
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

	void			SetUTF_8Text(const char8_t* name);

	void			SetFontSize(int size);

	void			SetColor(Vector3 color);


	class Font*		GetFont()const { return mFont; }
};