#pragma once
#include "Image.h"
#include "Font.h"

/*
* ===�G���W����������/Engine internal processing===
*/

// �e�L�X�g��\�����邽�߂̃N���X
// ��Ƀt�H���g�ƃe�L�X�g�̓��e���Ǘ����܂��B
class Text : public Image
{
private:
	// �e�L�X�g�̖��O
	string			mName;
	// UTF-8�`���̃e�L�X�g���e
	ccp_String      mText;
	// �t�H���g
	class Font*		mFont;
	// �e�L�X�g�̈ʒu
	Vector2			mDimensions;
	
	bool			mHighlighted;
	// �e�L�X�g�̃t�H���g�T�C�Y
	int				mFontSize;
	// �e�L�X�g�̐F
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