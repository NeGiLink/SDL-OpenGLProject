#pragma once
#include "Math.h"
#include "Texture.h"
#include "Shader.h"
#include "WinMain.h"
#include "Font.h"
#include "Image.h"
#include "Text.h"

//�{�^��UI�̃N���X
class Button : Image
{
public:
	Button(const string& name, class Font* font,
		std::function<void()> onClick,
		const Vector2& pos, const Vector2& dims);
	~Button();

	// �{�^���̖��O��ݒ肵�܂�
	void					SetName(const string& name);


	void SetButtonText(class Texture* texture) { mButtonTex = texture; }
	// Getters/setters
	class Texture*			GetNameTex() { return mNameTex; }
	const Vector2&			GetPosition() const { return mPosition; }
	void					SetHighlighted(bool sel) { mHighlighted = sel; }
	bool					GetHighlighted() const { return mHighlighted; }

	// �|�C���g���{�^���̋��E���ɂ���ꍇ��true��Ԃ��܂�
	bool					ContainsPoint(const Vector2& pt) const;
	// �{�^�����N���b�N���ꂽ�Ƃ��ɌĂяo����܂�
	void					OnClick();
	void					Draw(class Shader* shader)override;
	// �摜��`�悷��֐�
	void					DrawTexture(class Shader* shader, class Texture* texture,
		const Vector2& offset = Vector2::Zero,
		Vector3 scale = Vector3(1.0f, 1.0f, 1.0f), float angle = 0);
private:
	std::function<void()>	mOnClick;

	string					mName;

	class Texture*			mButtonTex;

	class Texture*			mNameTex;

	class Font*				mFont;

	Vector2					mPosition;

	Vector2					mDimensions;

	bool					mHighlighted;
};