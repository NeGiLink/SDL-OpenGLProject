#pragma once
#include "Math.h"
#include "Texture.h"
#include "Shader.h"
#include "WinMain.h"
#include "Font.h"
#include "Image.h"
#include "Text.h"

//ボタンUIのクラス
class Button : Image
{
public:
	Button(const string& name, class Font* font,
		std::function<void()> onClick,
		const Vector2& pos, const Vector2& dims);
	~Button();

	// ボタンの名前を設定します
	void					SetName(const string& name);


	void SetButtonText(class Texture* texture) { mButtonTex = texture; }
	// Getters/setters
	class Texture*			GetNameTex() { return mNameTex; }
	const Vector2&			GetPosition() const { return mPosition; }
	void					SetHighlighted(bool sel) { mHighlighted = sel; }
	bool					GetHighlighted() const { return mHighlighted; }

	// ポイントがボタンの境界内にある場合はtrueを返します
	bool					ContainsPoint(const Vector2& pt) const;
	// ボタンがクリックされたときに呼び出されます
	void					OnClick();
	void					Draw(class Shader* shader)override;
	// 画像を描画する関数
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