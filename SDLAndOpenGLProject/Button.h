#pragma once
#include "Math.h"
#include "Texture.h"
#include "Shader.h"
#include "WinMain.h"
#include "Font.h"
#include "Image.h"
#include "Text.h"

//���Ќ������������t�@�C��
//�{�^��UI�̃N���X
class Button : public Image
{
public:
	Button(const string& name, class Font* font,
		std::function<void()> onClick,
		const Vector2& pos, const Vector2& dims);
	Button(const char8_t* name, class Font* font,
		std::function<void()> onClick,
		const Vector2& pos, const Vector2& dims);
	~Button();

	void					Update(float deltaTime)override;

	void					SetButtonText(class Texture* texture);
	// Getters/setters
	class Text*				GetNameText() { return mNameText; }
	const Vector2&			GetPosition() const { return mPosition; }
	void					SetHighlighted(bool sel) { mHighlighted = sel; }
	bool					GetHighlighted() const { return mHighlighted; }

	// �|�C���g���{�^���̋��E���ɂ���ꍇ��true��Ԃ��܂�
	bool					ContainsPoint(const Vector2& pt) const;
	// �{�^�����N���b�N���ꂽ�Ƃ��ɌĂяo����܂�
	void					OnClick();

	Coroutine				DicideButton();
private:
	std::function<void()>	mOnClick;

	float					mClickCount;

	float					mDicideButton;

	string					mName;

	class Image*			mButtonImage;

	class Text*				mNameText;

	class Font*				mFont;

	Vector2					mPosition;

	Vector2					mDimensions;

	bool					mHighlighted;

	Vector2					mBaseButtonPosition;
};