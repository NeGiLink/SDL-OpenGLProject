#pragma once
#include "Math.h"
#include <cstdint>
#include <string>
#include <functional>
#include <vector>

//ボタンUIのクラス
class Button
{
public:
	Button(const std::string& name, class Font* font,
		std::function<void()> onClick,
		const Vector2& pos, const Vector2& dims);
	~Button();

	// ボタンの名前を設定します
	void SetName(const std::string& name);

	// Getters/setters
	class Texture* GetNameTex() { return mNameTex; }
	const Vector2& GetPosition() const { return mPosition; }
	void SetHighlighted(bool sel) { mHighlighted = sel; }
	bool GetHighlighted() const { return mHighlighted; }

	// ポイントがボタンの境界内にある場合はtrueを返します
	bool ContainsPoint(const Vector2& pt) const;
	// ボタンがクリックされたときに呼び出されます
	void OnClick();
private:
	std::function<void()>	mOnClick;
	
	std::string				mName;
	
	class Texture*			mNameTex;
	
	class Font*				mFont;
	
	Vector2					mPosition;
	
	Vector2					mDimensions;
	
	bool					mHighlighted;
};

//ポーズ、ダイアログなどのUIの基底クラス
class UIScreen
{
public:
	UIScreen();
	virtual ~UIScreen();
	// UIScreenのサブクラスはこれらをオーバーライドできます
	virtual void Update(float deltaTime);
	virtual void Draw(class Shader* shader);
	virtual void ProcessInput(const struct InputState& keys);
	virtual void HandleKeyPress(int key);
	// UIがアクティブを管理するタグ
	enum UIState
	{
		EActive,
		EClosing
	};
	// 状態を閉鎖に設定
	void Close();
	// UI画面の状態を取得する
	UIState GetState() const { return mState; }
	// タイトルテキストを変更する
	void SetTitle(const std::string& text,
		const Vector3& color = Color::White,
		int pointSize = 40);
	// この画面にボタンを追加する関数
	void AddButton(const std::string& name, std::function<void()> onClick);
protected:
	// 画像を描画する関数
	void DrawTexture(class Shader* shader, class Texture* texture,
		const Vector2& offset = Vector2::Zero,
		Vector3 scale = Vector3(1.0f, 1.0f, 1.0f), float angle = 0);
	// マウスモードを相対モードに設定するかどうか
	void SetRelativeMouseMode(bool relative);
	class BaseScene*		mGame;

	class Text*				mTitleFont;
	class Image*			mTitle;
	class Image*			mBackground;
	class Image*			mButtonOn;
	class Image*			mButtonOff;

	// 位置を設定する
	Vector2					mTitlePos;
	Vector2					mNextButtonPos;
	Vector2					mBGPos;

	// 状態
	UIState					mState;
	// ボタンのリスト
	std::vector<Button*>	mButtons;
};