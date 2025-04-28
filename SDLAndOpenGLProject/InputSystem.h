#pragma once
#include <SDL3/SDL_scancode.h>
#include <SDL3/SDL_gamepad.h>
#include <SDL3/SDL_mouse.h>
#include "Math.h"

/*
* ���͏������܂Ƃ߂��t�@�C��
* �L�[�{�[�h�A�}�E�X�A�R���g���[���[�̓��͂��擾�\
*/

// �{�^���̏��
enum ButtonState
{
	ENone,
	EPressed,
	EReleased,
	EHeld
};

// �L�[�{�[�h���͂̃w���p�[�N���X
class KeyboardState
{
public:
	// InputSystem�̍X�V
	friend class InputSystem;
	// �L�[�̐^�U�l�i�^�܂��͋U�j�݂̂��擾
	bool GetKeyValue(SDL_Scancode keyCode) const;
	// ���݂̃t���[���ƑO�̃t���[���Ɋ�Â��ď�Ԃ��擾
	bool GetKeyDown(SDL_Scancode keyCode) const;
	bool GetKeyUp(SDL_Scancode keyCode) const;
	bool GetKey(SDL_Scancode keyCode) const;
private:
	const bool*		mCurrState;
	Uint8			mPrevState[SDL_SCANCODE_COUNT];
};

// �}�E�X���͂̃w���p�[�N���X
class MouseState
{
public:
	friend class InputSystem;

	// �}�E�X�̈ʒu���
	const Vector2& GetPosition() const { return mMousePos; }
	const Vector2& GetScrollWheel() const { return mScrollWheel; }
	bool IsRelative() const { return mIsRelative; }

	// �}�E�X�̓��͏��
	bool GetButtonValue(int button) const;
	ButtonState GetButtonState(int button) const;
	bool GetButtonDown(int button) const;
	bool GetButtonUp(int button) const;
	bool GetButton(int button) const;
private:
	// ���݂̃}�E�X�̈ʒu��ۑ�
	Vector2 mMousePos;
	// �X�N���[���z�C�[���̈ړ�
	Vector2 mScrollWheel;
	// �{�^���f�[�^��ۑ�
	Uint32	mCurrButtons;
	Uint32	mPrevButtons;
	// ���΃}�E�X���[�h�t���O
	bool	mIsRelative;
};

// �R���g���[���[���͂̃w���p�[�N���X
class ControllerState
{
public:
	friend class InputSystem;

	// �{�^�����͏��
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

	// ����/�O�̃{�^�����
	Uint8	mCurrButtons[SDL_GAMEPAD_BUTTON_COUNT];
	Uint8	mPrevButtons[SDL_GAMEPAD_BUTTON_COUNT];
	// ��/�E�X�e�B�b�N
	Vector2 mLeftStick;
	Vector2 mRightStick;
	// ��/�E�g���K�[
	float	mLeftTrigger;
	float	mRightTrigger;
	// �R���g���[���[�ڑ��t���O
	bool	mIsConnected;
};

// ���͂̌��݂̏�Ԃ��܂ރ��b�p�[
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

	// SDL_PollEvents���[�v�̒��O�ɌĂяo���֐�
	static void PrepareForUpdate();
	
	// SDL_PollEvents���[�v�̌�ɌĂяo���֐�
	static void Update();
	
	// ���̓V�X�e����SDL�C�x���g���������邽�߂ɌĂяo���֐�
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