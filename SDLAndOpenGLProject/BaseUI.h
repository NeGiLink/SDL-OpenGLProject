#pragma once
#include "Math.h"
#include "Texture.h"
#include "Shader.h"
#include "WinMain.h"
#include "BaseScene.h"


class BaseUI
{
public:
	// UIがアクティブか閉じているかを追跡します
	enum UIState
	{
		EActive,
		EClosing,
		EDestroy
	};
								BaseUI();
		virtual					~BaseUI();
		//読み込み処理
		virtual void			Load(string file);
		virtual void			Update(float deltaTime);
		virtual void			Draw(class Shader* shader);
		// テクスチャを描くための関数
		void					DrawTexture(class Shader* shader);

		Vector4					UVCalculation();

		Matrix4					WorldMatrixCalculation();

		virtual void			UnLoad();
		// 状態を閉鎖に設定
		void					Close();

		void					Active();

		//***Getter***
		virtual SDL_Rect		GetSDL_Rect() { return mTextureRect; }

		// UI画面の状態を取得する
		UIState					GetState() const { return mState; }

		

		//***Setter***
		//画像を設定
		virtual void			SetTexture(class Texture* texture);
		//画像の位置を設定
		virtual void			SetPosition(Vector2 pos);
		//画像のスケーリングを設定
		virtual void			SetScale(Vector3 scale);
		virtual void			SetSDL_Rect(SDL_Rect rect) { mTextureRect = rect; }
		//画像の回転を行う
		virtual void			SetAngleZ(float angle);

		virtual void 			SetState(UIState state) { mState = state; }

protected:
	class BaseScene* mGame;

	// Configure positions
	Vector2					mTexturePos;
	//スケーリング
	Vector3					mTexScale;

	float					mAngleZ;

	SDL_Rect				mTextureRect;

	// State
	UIState					mState;
};

