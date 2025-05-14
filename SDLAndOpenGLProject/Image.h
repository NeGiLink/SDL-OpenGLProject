#pragma once
#include "Math.h"
#include "Texture.h"
#include "Shader.h"
#include "WinMain.h"
#include "BaseScene.h"

//画像描画をカプセル化したクラス
class Image
{
public:
							Image(bool active = true);
	virtual					~Image();
	virtual void			Load(string file);
	virtual void			SetTexture(class Texture* texture);
	virtual void			SetPosition(Vector2 pos);
	virtual void			SetScale(Vector3 scale);
	virtual void			SetAngleZ(float angle);
	virtual void			Update(float deltaTime);
	virtual void			Draw(class Shader* shader);
	virtual void			UnLoad();
	// UIがアクティブか閉じているかを追跡します
	enum UIState
	{
		EActive,
		EClosing,
		EDestroy
	};
	// 状態を閉鎖に設定
	void					Close();

	void					Active();
	// UI画面の状態を取得する
	UIState					GetState() const { return mState; }

	void					SetUpdateTogether(bool active) { updateTogether = active; }

	class Texture*			GetTexture() const { return mTexture; }
protected:
	// テクスチャを描くための関数
	void					DrawTexture(class Shader* shader, class Texture* texture,
							const Vector2& offset = Vector2::Zero,
							Vector3 scale = Vector3(1.0f, 1.0f, 1.0f),float angle = 0);
	class BaseScene*		mGame;

	class Texture*			mTexture;

	// Configure positions
	Vector2					mTexturePos;

	Vector3					mTexScale;

	float					mAngleZ;

	// State
	UIState					mState;

	bool					updateTogether = true;
};

