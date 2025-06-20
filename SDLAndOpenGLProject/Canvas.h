#pragma once
#include "Math.h"
#include "Texture.h"
#include "Shader.h"
#include "WinMain.h"
#include "Font.h"
#include "Image.h"
#include "Text.h"

#include "Button.h"

/*
* ===エンジン内部処理/Engine internal processing===
*/

//ポーズ、ダイアログなどのUIの基底クラス
// UnityのCanvasに近いクラス
class Canvas
{
public:
	// UIがアクティブを管理するタグ
	enum UIState
	{
		EActive,
		EClosing,
		EDestroy
	};
protected:
	// 画像を描画する関数
	void					DrawTexture(class Shader* shader, class Texture* texture,
		const Vector2& offset = Vector2::Zero,
		Vector3 scale = Vector3(1.0f, 1.0f, 1.0f), float angle = 0);
	class BaseScene* mGame;

	class Text* mTitleFont;
	class Image* mTitle;
	class Image* mBackground;

	class Texture* mButtonOn;
	class Texture* mButtonOff;

	// 位置を設定する
	Vector2					mTitlePos;
	Vector2					mNextButtonPos;
	Vector2					mBGPos;

	// 状態
	UIState					mState;
	// ボタンのリスト
	vector<Button*>			mButtons;

	vector<Image*>			mImages;
public:
							Canvas();
	virtual					~Canvas();
	// UIScreenのサブクラスはこれらをオーバーライドできます
	virtual void			Update(float deltaTime);
	virtual void			Draw(class Shader* shader);
	virtual void			ProcessInput(const struct InputState& keys);
	virtual void			HandleKeyPress(int key);

	// 状態を閉鎖に設定
	void					Close();
	// UI画面の状態を取得する
	UIState					GetState() const { return mState; }
	void					SetState(UIState state);
	// タイトルテキストを変更する
	void					SetTitle(const string& text,
							const Vector3& color = Color::White,
							int pointSize = 40);
	// この画面にボタンを追加する関数
	void					AddButton(const string& name, std::function<void()> onClick);
	class Button*			CreateButton(const string& name,const Vector2& pos, std::function<void()> onClick);
	class Button*			CreateButton(const char8_t* name,const Vector2& pos, std::function<void()> onClick);
	// マウスモードを相対モードに設定するかどうか
	void					SetRelativeMouseMode(bool relative);

	void					AddChildUIImage(Image* image);
};