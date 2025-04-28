#pragma once
#include <SDL3/SDL_scancode.h>
#include <SDL3/SDL_gamepad.h>
#include <SDL3/SDL_mouse.h>
#include "Math.h"

/*
* 入力処理をまとめたファイル
* キーボード、マウス、コントローラーの入力を取得可能
*/

// ボタンの状態
enum ButtonState
{
	ENone,
	EPressed,
	EReleased,
	EHeld
};

// キーボード入力のヘルパークラス
class KeyboardState
{
public:
	// InputSystemの更新
	friend class InputSystem;
	// キーの真偽値（真または偽）のみを取得
	bool GetKeyValue(SDL_Scancode keyCode) const;
	// 現在のフレームと前のフレームに基づいて状態を取得
	bool GetKeyDown(SDL_Scancode keyCode) const;
	bool GetKeyUp(SDL_Scancode keyCode) const;
	bool GetKey(SDL_Scancode keyCode) const;
private:
	const bool*		mCurrState;
	Uint8			mPrevState[SDL_SCANCODE_COUNT];
};

// マウス入力のヘルパークラス
class MouseState
{
public:
	friend class InputSystem;

	// マウスの位置情報
	const Vector2& GetPosition() const { return mMousePos; }
	const Vector2& GetScrollWheel() const { return mScrollWheel; }
	bool IsRelative() const { return mIsRelative; }

	// マウスの入力情報
	bool GetButtonValue(int button) const;
	ButtonState GetButtonState(int button) const;
	bool GetButtonDown(int button) const;
	bool GetButtonUp(int button) const;
	bool GetButton(int button) const;
private:
	// 現在のマウスの位置を保存
	Vector2 mMousePos;
	// スクロールホイールの移動
	Vector2 mScrollWheel;
	// ボタンデータを保存
	Uint32	mCurrButtons;
	Uint32	mPrevButtons;
	// 相対マウスモードフラグ
	bool	mIsRelative;
};

// コントローラー入力のヘルパークラス
class ControllerState
{
public:
	friend class InputSystem;

	// ボタン入力情報
	bool GetButtonValue(SDL_GamepadButton button) const;
	ButtonState GetButtonState(SDL_GamepadButton button) const;

	bool GetButtonDown(SDL_GamepadButton button) const;
	bool GetButtonUp(SDL_GamepadButton button) const;
	bool GetButton(SDL_GamepadButton button) const;

	const Vector2& GetLeftStick() const { return mLeftStick; }
	const Vector2& GetRightStick() const { return mRightStick; }
	float GetLeftTrigger() const { return mLeftTrigger; }
	float GetRightTrigger() const { return mRightTrigger; }

	bool GetIsConnected() const { return mIsConnected; }
private:

	// 現在/前のボタン情報
	Uint8	mCurrButtons[SDL_GAMEPAD_BUTTON_COUNT];
	Uint8	mPrevButtons[SDL_GAMEPAD_BUTTON_COUNT];
	// 左/右スティック
	Vector2 mLeftStick;
	Vector2 mRightStick;
	// 左/右トリガー
	float	mLeftTrigger;
	float	mRightTrigger;
	// コントローラー接続フラグ
	bool	mIsConnected;
};

// 入力の現在の状態を含むラッパー
struct InputState
{
	KeyboardState	Keyboard;
	MouseState		Mouse;
	ControllerState Controller;
};

class InputSystem
{
public:
	static bool Initialize();
	static void Shutdown();

	// SDL_PollEventsループの直前に呼び出す関数
	static void PrepareForUpdate();
	
	// SDL_PollEventsループの後に呼び出す関数
	static void Update();
	
	// 入力システムでSDLイベントを処理するために呼び出す関数
	static void ProcessEvent(union SDL_Event& event);

	static const InputState& GetState(){ return mState; }

	static void SetRelativeMouseMode(bool value);

	static void SetSDL_Window(SDL_Window* window) { mWindow = window; }
private:
	static float Filter1D(int input);
	
	static Vector2 Filter2D(int inputX, int inputY);
	
	static InputState		mState;

	static SDL_Gamepad*		mController;

	static SDL_Window*		mWindow;
};