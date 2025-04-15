#pragma once
#include <SDL3/SDL_scancode.h>
#include <SDL3/SDL_gamepad.h>
#include <SDL3/SDL_mouse.h>
#include "Math.h"

// The different button states
enum ButtonState
{
	ENone,
	EPressed,
	EReleased,
	EHeld
};

// Helper for keyboard input
class KeyboardState
{
public:
	// Friend so InputSystem can easily update it
	friend class InputSystem;
	// Get just the boolean true/false value of key
	bool GetKeyValue(SDL_Scancode keyCode) const;
	// Get a state based on current and previous frame
	ButtonState GetKeyState(SDL_Scancode keyCode) const;
private:
	const bool* mCurrState;
	Uint8 mPrevState[SDL_SCANCODE_COUNT];
};

// Helper for mouse input
class MouseState
{
public:
	friend class InputSystem;

	// For mouse position
	const Vector2& GetPosition() const { return mMousePos; }
	const Vector2& GetScrollWheel() const { return mScrollWheel; }
	bool IsRelative() const { return mIsRelative; }

	// For buttons
	bool GetButtonValue(int button) const;
	ButtonState GetButtonState(int button) const;
private:
	// Store current mouse position
	Vector2 mMousePos;
	// Motion of scroll wheel
	Vector2 mScrollWheel;
	// Store button data
	Uint32 mCurrButtons;
	Uint32 mPrevButtons;
	// Are we in relative mouse mode
	bool mIsRelative;
};

// Helper for controller input
class ControllerState
{
public:
	friend class InputSystem;

	// For buttons
	bool GetButtonValue(SDL_GamepadButton button) const;
	ButtonState GetButtonState(SDL_GamepadButton button) const;

	const Vector2& GetLeftStick() const { return mLeftStick; }
	const Vector2& GetRightStick() const { return mRightStick; }
	float GetLeftTrigger() const { return mLeftTrigger; }
	float GetRightTrigger() const { return mRightTrigger; }

	bool GetIsConnected() const { return mIsConnected; }
private:

	// Current/previous buttons
	Uint8 mCurrButtons[SDL_GAMEPAD_BUTTON_COUNT];
	Uint8 mPrevButtons[SDL_GAMEPAD_BUTTON_COUNT];
	// Left/right sticks
	Vector2 mLeftStick;
	Vector2 mRightStick;
	// Left/right trigger
	float mLeftTrigger;
	float mRightTrigger;
	// Is this controller connected?
	bool mIsConnected;
};

// Wrapper that contains current state of input
struct InputState
{
	KeyboardState Keyboard;
	MouseState Mouse;
	ControllerState Controller;
};

class InputSystem
{
public:
	static bool Initialize();
	static void Shutdown();

	// Called right before SDL_PollEvents loop
	static void PrepareForUpdate();
	
	// Called after SDL_PollEvents loop
	static void Update();
	
	// Called to process an SDL event in input system
	static void ProcessEvent(union SDL_Event& event);

	static const InputState& GetState(){ return mState; }

	static void SetRelativeMouseMode(bool value);

	static void SetSDL_Window(SDL_Window* window) { mWindow = window; }
private:
	static float Filter1D(int input);
	
	static Vector2 Filter2D(int inputX, int inputY);
	
	static InputState mState;

	static SDL_Gamepad* mController;

	static SDL_Window* mWindow;
};