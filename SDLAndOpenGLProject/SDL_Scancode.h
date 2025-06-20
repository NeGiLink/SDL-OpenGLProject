#pragma once
#include <SDL3/SDL_scancode.h>
#include <SDL3/SDL_gamepad.h>
#include <SDL3/SDL_mouse.h>

/*
* ===エンジン内部処理/Engine internal processing===
*/

//入力のenumをdefineでまとめたファイル
//キーボード、マウス、コントローラーの入力をまとめている
// SDLのスキャンコードを使用している

#define KEY_UNKNOWN					SDL_Scancode::SDL_SCANCODE_UNKNOWN

#define KEY_A						SDL_Scancode::SDL_SCANCODE_A
#define KEY_B						SDL_Scancode::SDL_SCANCODE_B
#define KEY_C						SDL_Scancode::SDL_SCANCODE_C
#define KEY_D						SDL_Scancode::SDL_SCANCODE_D
#define KEY_E						SDL_Scancode::SDL_SCANCODE_E
#define KEY_F						SDL_Scancode::SDL_SCANCODE_F
#define KEY_G						SDL_Scancode::SDL_SCANCODE_G
#define KEY_H						SDL_Scancode::SDL_SCANCODE_H
#define KEY_I						SDL_Scancode::SDL_SCANCODE_I
#define KEY_J						SDL_Scancode::SDL_SCANCODE_J
#define KEY_K						SDL_Scancode::SDL_SCANCODE_K
#define KEY_L						SDL_Scancode::SDL_SCANCODE_L
#define KEY_M						SDL_Scancode::SDL_SCANCODE_M
#define KEY_N						SDL_Scancode::SDL_SCANCODE_N
#define KEY_O						SDL_Scancode::SDL_SCANCODE_O
#define KEY_P						SDL_Scancode::SDL_SCANCODE_P
#define KEY_Q						SDL_Scancode::SDL_SCANCODE_Q
#define KEY_R						SDL_Scancode::SDL_SCANCODE_R
#define KEY_S						SDL_Scancode::SDL_SCANCODE_S
#define KEY_T						SDL_Scancode::SDL_SCANCODE_T
#define KEY_U						SDL_Scancode::SDL_SCANCODE_U
#define KEY_V						SDL_Scancode::SDL_SCANCODE_V
#define KEY_W						SDL_Scancode::SDL_SCANCODE_W
#define KEY_X						SDL_Scancode::SDL_SCANCODE_X
#define KEY_Y						SDL_Scancode::SDL_SCANCODE_Y
#define KEY_Z						SDL_Scancode::SDL_SCANCODE_Z

#define KEY_1						SDL_Scancode::SDL_SCANCODE_1
#define KEY_2						SDL_Scancode::SDL_SCANCODE_2
#define KEY_3						SDL_Scancode::SDL_SCANCODE_3
#define KEY_4						SDL_Scancode::SDL_SCANCODE_4
#define KEY_5						SDL_Scancode::SDL_SCANCODE_5
#define KEY_6						SDL_Scancode::SDL_SCANCODE_6
#define KEY_7						SDL_Scancode::SDL_SCANCODE_7
#define KEY_8						SDL_Scancode::SDL_SCANCODE_8
#define KEY_9						SDL_Scancode::SDL_SCANCODE_9
#define KEY_0						SDL_Scancode::SDL_SCANCODE_0

#define KEY_RETURN					SDL_Scancode::SDL_SCANCODE_RETURN
#define KEY_ESCAPE					SDL_Scancode::SDL_SCANCODE_ESCAPE
#define KEY_BACKSPACE				SDL_Scancode::SDL_SCANCODE_BACKSPACE
#define KEY_TAB						SDL_Scancode::SDL_SCANCODE_TAB
#define KEY_SPACE					SDL_Scancode::SDL_SCANCODE_SPACE

#define KEY_MINUS					SDL_Scancode::SDL_SCANCODE_MINUS
#define KEY_EQUALS					SDL_Scancode::SDL_SCANCODE_EQUALS
#define KEY_LEFTBRACKET				SDL_Scancode::SDL_SCANCODE_LEFTBRACKET
#define KEY_RIGHTBRACKET			SDL_Scancode::SDL_SCANCODE_RIGHTBRACKET
#define KEY_BACKSLASH				SDL_Scancode::SDL_SCANCODE_BACKSLASH

#define KEY_NONUSHASH				SDL_Scancode::SDL_SCANCODE_NONUSHASH

#define KEY_SEMICOLON				SDL_Scancode::SDL_SCANCODE_SEMICOLON
#define KEY_APOSTROPHE				SDL_Scancode::SDL_SCANCODE_APOSTROPHE
#define KEY_GRAVE					SDL_Scancode::SDL_SCANCODE_GRAVE

#define KEY_COMMA					SDL_Scancode::SDL_SCANCODE_COMMA
#define KEY_PERIOD					SDL_Scancode::SDL_SCANCODE_PERIOD
#define KEY_SLASH					SDL_Scancode::SDL_SCANCODE_SLASH

#define KEY_CAPSLOCK				SDL_Scancode::SDL_SCANCODE_CAPSLOCK

#define KEY_F1						SDL_Scancode::SDL_SCANCODE_F1
#define KEY_F2						SDL_Scancode::SDL_SCANCODE_F2
#define KEY_F3						SDL_Scancode::SDL_SCANCODE_F3
#define KEY_F4						SDL_Scancode::SDL_SCANCODE_F4
#define KEY_F5						SDL_Scancode::SDL_SCANCODE_F5
#define KEY_F6						SDL_Scancode::SDL_SCANCODE_F6
#define KEY_F7						SDL_Scancode::SDL_SCANCODE_F7
#define KEY_F8						SDL_Scancode::SDL_SCANCODE_F8
#define KEY_F9						SDL_Scancode::SDL_SCANCODE_F9
#define KEY_F10						SDL_Scancode::SDL_SCANCODE_F10
#define KEY_F11						SDL_Scancode::SDL_SCANCODE_F11
#define KEY_F12						SDL_Scancode::SDL_SCANCODE_F12

#define KEY_PRINTSCREEN				SDL_Scancode::SDL_SCANCODE_PRINTSCREEN
#define KEY_SCROLLLOCK				SDL_Scancode::SDL_SCANCODE_SCROLLLOCK
#define KEY_PAUSE					SDL_Scancode::SDL_SCANCODE_PAUSE
#define KEY_INSERT					SDL_Scancode::SDL_SCANCODE_INSERT 

#define KEY_HOME					SDL_Scancode::SDL_SCANCODE_HOME
#define KEY_PAGEUP					SDL_Scancode::SDL_SCANCODE_PAGEUP
#define KEY_DELETE					SDL_Scancode::SDL_SCANCODE_DELETE
#define KEY_END						SDL_Scancode::SDL_SCANCODE_END
#define KEY_PAGEDOWN				SDL_Scancode::SDL_SCANCODE_PAGEDOWN
#define KEY_RIGHT					SDL_Scancode::SDL_SCANCODE_RIGHT
#define KEY_LEFT					SDL_Scancode::SDL_SCANCODE_LEFT
#define KEY_DOWN					SDL_Scancode::SDL_SCANCODE_DOWN
#define KEY_UP						SDL_Scancode::SDL_SCANCODE_UP

#define KEY_NUMLOCKCLEAR			SDL_Scancode::SDL_SCANCODE_NUMLOCKCLEAR

#define KEY_KP_DIVIDE				SDL_Scancode::SDL_SCANCODE_KP_DIVIDE
#define KEY_KP_MULTIPLY				SDL_Scancode::SDL_SCANCODE_KP_MULTIPLY
#define KEY_KP_MINUS				SDL_Scancode::SDL_SCANCODE_KP_MINUS
#define KEY_KP_PLUS					SDL_Scancode::SDL_SCANCODE_KP_PLUS
#define KEY_KP_ENTER				SDL_Scancode::SDL_SCANCODE_KP_ENTER
#define KEY_KP_1					SDL_Scancode::SDL_SCANCODE_KP_1
#define KEY_KP_2					SDL_Scancode::SDL_SCANCODE_KP_2
#define KEY_KP_3					SDL_Scancode::SDL_SCANCODE_KP_3
#define KEY_KP_4					SDL_Scancode::SDL_SCANCODE_KP_4
#define KEY_KP_5					SDL_Scancode::SDL_SCANCODE_KP_5
#define KEY_KP_6					SDL_Scancode::SDL_SCANCODE_KP_6
#define KEY_KP_7					SDL_Scancode::SDL_SCANCODE_KP_7
#define KEY_KP_8					SDL_Scancode::SDL_SCANCODE_KP_8
#define KEY_KP_9					SDL_Scancode::SDL_SCANCODE_KP_9
#define KEY_KP_0					SDL_Scancode::SDL_SCANCODE_KP_0
#define KEY_KP_PERIOD				SDL_Scancode::SDL_SCANCODE_KP_PERIOD

#define KEY_NONUSBACKSLASH			SDL_Scancode::SDL_SCANCODE_NONUSBACKSLASH

#define KEY_APPLICATION				SDL_Scancode::SDL_SCANCODE_APPLICATION 
#define KEY_POWER					SDL_Scancode::SDL_SCANCODE_POWER 

#define KEY_KP_EQUALS				SDL_Scancode::SDL_SCANCODE_KP_EQUALS
#define KEY_F13						SDL_Scancode::SDL_SCANCODE_F13
#define KEY_F14						SDL_Scancode::SDL_SCANCODE_F14
#define KEY_F15						SDL_Scancode::SDL_SCANCODE_F15
#define KEY_F16						SDL_Scancode::SDL_SCANCODE_F16
#define KEY_F17						SDL_Scancode::SDL_SCANCODE_F17
#define KEY_F18						SDL_Scancode::SDL_SCANCODE_F18
#define KEY_F19						SDL_Scancode::SDL_SCANCODE_F19
#define KEY_F20						SDL_Scancode::SDL_SCANCODE_F20
#define KEY_F21						SDL_Scancode::SDL_SCANCODE_F21
#define KEY_F22						SDL_Scancode::SDL_SCANCODE_F22
#define KEY_F23						SDL_Scancode::SDL_SCANCODE_F23
#define KEY_F24						SDL_Scancode::SDL_SCANCODE_F24
#define KEY_EXECUTE					SDL_Scancode::SDL_SCANCODE_EXECUTE
#define KEY_HELP					SDL_Scancode::SDL_SCANCODE_HELP
#define KEY_MENU					SDL_Scancode::SDL_SCANCODE_MENU
#define KEY_SELECT					SDL_Scancode::SDL_SCANCODE_SELECT
#define KEY_STOP					SDL_Scancode::SDL_SCANCODE_STOP
#define KEY_AGAIN					SDL_Scancode::SDL_SCANCODE_AGAIN
#define KEY_UNDO					SDL_Scancode::SDL_SCANCODE_UNDO
#define KEY_CUT						SDL_Scancode::SDL_SCANCODE_CUT
#define KEY_COPY					SDL_Scancode::SDL_SCANCODE_COPY
#define KEY_PASTE					SDL_Scancode::SDL_SCANCODE_PASTE
#define KEY_FIND					SDL_Scancode::SDL_SCANCODE_FIND
#define KEY_MUTE					SDL_Scancode::SDL_SCANCODE_MUTE
#define KEY_VOLUMEUP				SDL_Scancode::SDL_SCANCODE_VOLUMEUP
#define KEY_VOLUMEDOWN				SDL_Scancode::SDL_SCANCODE_VOLUMEDOWN

#define KEY_KP_COMMA				SDL_Scancode::SDL_SCANCODE_KP_COMMA
#define KEY_KP_EQUALSAS400			SDL_Scancode::SDL_SCANCODE_KP_EQUALSAS400

#define KEY_INTERNATIONAL1			SDL_Scancode::SDL_SCANCODE_INTERNATIONAL1

#define KEY_INTERNATIONAL2			SDL_Scancode::SDL_SCANCODE_INTERNATIONAL2
#define KEY_INTERNATIONAL3			SDL_Scancode::SDL_SCANCODE_INTERNATIONAL3
#define KEY_INTERNATIONAL4			SDL_Scancode::SDL_SCANCODE_INTERNATIONAL4
#define KEY_INTERNATIONAL5			SDL_Scancode::SDL_SCANCODE_INTERNATIONAL5
#define KEY_INTERNATIONAL6			SDL_Scancode::SDL_SCANCODE_INTERNATIONAL6
#define KEY_INTERNATIONAL7			SDL_Scancode::SDL_SCANCODE_INTERNATIONAL7
#define KEY_INTERNATIONAL8			SDL_Scancode::SDL_SCANCODE_INTERNATIONAL8
#define KEY_INTERNATIONAL9			SDL_Scancode::SDL_SCANCODE_INTERNATIONAL9
#define KEY_LANG1					SDL_Scancode::SDL_SCANCODE_LANG1
#define KEY_LANG2					SDL_Scancode::SDL_SCANCODE_LANG2
#define KEY_LANG3					SDL_Scancode::SDL_SCANCODE_LANG3
#define KEY_LANG4					SDL_Scancode::SDL_SCANCODE_LANG4
#define KEY_LANG5					SDL_Scancode::SDL_SCANCODE_LANG5
#define KEY_LANG6					SDL_Scancode::SDL_SCANCODE_LANG6
#define KEY_LANG7					SDL_Scancode::SDL_SCANCODE_LANG7
#define KEY_LANG8					SDL_Scancode::SDL_SCANCODE_LANG8
#define KEY_LANG9					SDL_Scancode::SDL_SCANCODE_LANG9

#define KEY_ALTERASE				SDL_Scancode::SDL_SCANCODE_ALTERASE
#define KEY_SYSREQ					SDL_Scancode::SDL_SCANCODE_SYSREQ
#define KEY_CANCEL					SDL_Scancode::SDL_SCANCODE_CANCEL
#define KEY_CLEAR					SDL_Scancode::SDL_SCANCODE_CLEAR
#define KEY_PRIOR					SDL_Scancode::SDL_SCANCODE_PRIOR
#define KEY_RETURN2					SDL_Scancode::SDL_SCANCODE_RETURN2
#define KEY_SEPARATOR				SDL_Scancode::SDL_SCANCODE_SEPARATOR
#define KEY_OUT						SDL_Scancode::SDL_SCANCODE_OUT
#define KEY_OPER					SDL_Scancode::SDL_SCANCODE_OPER
#define KEY_CLEARAGAIN				SDL_Scancode::SDL_SCANCODE_CLEARAGAIN
#define KEY_CRSEL					SDL_Scancode::SDL_SCANCODE_CRSEL
#define KEY_EXSEL					SDL_Scancode::SDL_SCANCODE_EXSEL

#define KEY_KP_00					SDL_Scancode::SDL_SCANCODE_KP_00
#define KEY_KP_000					SDL_Scancode::SDL_SCANCODE_KP_000
#define KEY_THOUSANDSSEPARATOR		SDL_Scancode::SDL_SCANCODE_THOUSANDSSEPARATOR
#define KEY_DECIMALSEPARATOR		SDL_Scancode::SDL_SCANCODE_DECIMALSEPARATOR
#define KEY_CURRENCYUNIT			SDL_Scancode::SDL_SCANCODE_CURRENCYUNIT
#define KEY_CURRENCYSUBUNIT			SDL_Scancode::SDL_SCANCODE_CURRENCYSUBUNIT
#define KEY_KP_LEFTPAREN			SDL_Scancode::SDL_SCANCODE_KP_LEFTPAREN
#define KEY_KP_RIGHTPAREN			SDL_Scancode::SDL_SCANCODE_KP_RIGHTPAREN
#define KEY_KP_LEFTBRACE			SDL_Scancode::SDL_SCANCODE_KP_LEFTBRACE
#define KEY_KP_RIGHTBRACE			SDL_Scancode::SDL_SCANCODE_KP_RIGHTBRACE
#define KEY_KP_TAB					SDL_Scancode::SDL_SCANCODE_KP_TAB
#define KEY_KP_BACKSPACE			SDL_Scancode::SDL_SCANCODE_KP_BACKSPACE
#define KEY_KP_A					SDL_Scancode::SDL_SCANCODE_KP_A
#define KEY_KP_B					SDL_Scancode::SDL_SCANCODE_KP_B
#define KEY_KP_C					SDL_Scancode::SDL_SCANCODE_KP_C
#define KEY_KP_D					SDL_Scancode::SDL_SCANCODE_KP_D
#define KEY_KP_E					SDL_Scancode::SDL_SCANCODE_KP_E
#define KEY_KP_F					SDL_Scancode::SDL_SCANCODE_KP_F
#define KEY_KP_XOR					SDL_Scancode::SDL_SCANCODE_KP_XOR
#define KEY_KP_POWER				SDL_Scancode::SDL_SCANCODE_KP_POWER
#define KEY_KP_PERCENT				SDL_Scancode::SDL_SCANCODE_KP_PERCENT
#define KEY_KP_LESS					SDL_Scancode::SDL_SCANCODE_KP_LESS
#define KEY_KP_GREATER				SDL_Scancode::SDL_SCANCODE_KP_GREATER
#define KEY_KP_AMPERSAND			SDL_Scancode::SDL_SCANCODE_KP_AMPERSAND
#define KEY_KP_DBLAMPERSAND			SDL_Scancode::SDL_SCANCODE_KP_DBLAMPERSAND
#define KEY_KP_VERTICALBAR			SDL_Scancode::SDL_SCANCODE_KP_VERTICALBAR
#define KEY_KP_DBLVERTICALBAR		SDL_Scancode::SDL_SCANCODE_KP_DBLVERTICALBAR
#define KEY_KP_COLON				SDL_Scancode::SDL_SCANCODE_KP_COLON
#define KEY_KP_HASH					SDL_Scancode::SDL_SCANCODE_KP_HASH
#define KEY_KP_SPACE				SDL_Scancode::SDL_SCANCODE_KP_SPACE
#define KEY_KP_AT					SDL_Scancode::SDL_SCANCODE_KP_AT
#define KEY_KP_EXCLAM				SDL_Scancode::SDL_SCANCODE_KP_EXCLAM
#define KEY_KP_MEMSTORE				SDL_Scancode::SDL_SCANCODE_KP_MEMSTORE
#define KEY_KP_MEMRECALL			SDL_Scancode::SDL_SCANCODE_KP_MEMRECALL
#define KEY_KP_MEMCLEAR				SDL_Scancode::SDL_SCANCODE_KP_MEMCLEAR
#define KEY_KP_MEMADD				SDL_Scancode::SDL_SCANCODE_KP_MEMADD
#define KEY_KP_MEMSUBTRACT			SDL_Scancode::SDL_SCANCODE_KP_MEMSUBTRACT
#define KEY_KP_MEMMULTIPLY			SDL_Scancode::SDL_SCANCODE_KP_MEMMULTIPLY
#define KEY_KP_MEMDIVIDE			SDL_Scancode::SDL_SCANCODE_KP_MEMDIVIDE
#define KEY_KP_PLUSMINUS			SDL_Scancode::SDL_SCANCODE_KP_PLUSMINUS
#define KEY_KP_CLEAR				SDL_Scancode::SDL_SCANCODE_KP_CLEAR
#define KEY_KP_CLEARENTRY			SDL_Scancode::SDL_SCANCODE_KP_CLEARENTRY
#define KEY_KP_BINARY				SDL_Scancode::SDL_SCANCODE_KP_BINARY
#define KEY_KP_OCTAL				SDL_Scancode::SDL_SCANCODE_KP_OCTAL
#define KEY_KP_DECIMAL				SDL_Scancode::SDL_SCANCODE_KP_DECIMAL
#define KEY_KP_HEXADECIMAL			SDL_Scancode::SDL_SCANCODE_KP_HEXADECIMAL

#define KEY_LCTRL					SDL_Scancode::SDL_SCANCODE_LCTRL
#define KEY_LSHIFT					SDL_Scancode::SDL_SCANCODE_LSHIFT
#define KEY_LALT					SDL_Scancode::SDL_SCANCODE_LALT
#define KEY_LGUI					SDL_Scancode::SDL_SCANCODE_LGUI
#define KEY_RCTRL					SDL_Scancode::SDL_SCANCODE_RCTRL
#define KEY_RSHIFT					SDL_Scancode::SDL_SCANCODE_RSHIFT
#define KEY_RALT					SDL_Scancode::SDL_SCANCODE_RALT
#define KEY_RGUI					SDL_Scancode::SDL_SCANCODE_RGUI

#define KEY_MODE					SDL_Scancode::SDL_SCANCODE_MODE

#define KEY_SLEEP					SDL_Scancode::SDL_SCANCODE_SLEEP
#define KEY_WAKE					SDL_Scancode::SDL_SCANCODE_WAKE

#define KEY_CHANNEL_INCREMENT		SDL_Scancode::SDL_SCANCODE_CHANNEL_INCREMENT
#define KEY_CHANNEL_DECREMENT		SDL_Scancode::SDL_SCANCODE_CHANNEL_DECREMENT

#define KEY_MEDIA_PLAY				SDL_Scancode::SDL_SCANCODE_MEDIA_PLAY
#define KEY_MEDIA_PAUSE				SDL_Scancode::SDL_SCANCODE_MEDIA_PAUSE
#define KEY_MEDIA_RECORD			SDL_Scancode::SDL_SCANCODE_MEDIA_RECORD
#define KEY_MEDIA_FAST_FORWARD		SDL_Scancode::SDL_SCANCODE_MEDIA_FAST_FORWARD
#define KEY_MEDIA_REWIND			SDL_Scancode::SDL_SCANCODE_MEDIA_REWIND
#define KEY_MEDIA_NEXT_TRACK		SDL_Scancode::SDL_SCANCODE_MEDIA_NEXT_TRACK
#define KEY_MEDIA_PREVIOUS_TRACK    SDL_Scancode::SDL_SCANCODE_MEDIA_PREVIOUS_TRACK
#define KEY_MEDIA_STOP				SDL_Scancode::SDL_SCANCODE_MEDIA_STOP
#define KEY_MEDIA_EJECT				SDL_Scancode::SDL_SCANCODE_MEDIA_EJECT
#define KEY_MEDIA_PLAY_PAUSE		SDL_Scancode::SDL_SCANCODE_MEDIA_PLAY_PAUSE
#define KEY_MEDIA_SELECT			SDL_Scancode::SDL_SCANCODE_MEDIA_SELECT

#define KEY_AC_NEW					SDL_Scancode::SDL_SCANCODE_AC_NEW
#define KEY_AC_OPEN					SDL_Scancode::SDL_SCANCODE_AC_OPEN
#define KEY_AC_CLOSE				SDL_Scancode::SDL_SCANCODE_AC_CLOSE
#define KEY_AC_EXIT					SDL_Scancode::SDL_SCANCODE_AC_EXIT
#define KEY_AC_SAVE					SDL_Scancode::SDL_SCANCODE_AC_SAVE
#define KEY_AC_PRINT				SDL_Scancode::SDL_SCANCODE_AC_PRINT
#define KEY_AC_PROPERTIES			SDL_Scancode::SDL_SCANCODE_AC_PROPERTIES

#define KEY_AC_SEARCH				SDL_Scancode::SDL_SCANCODE_AC_SEARCH
#define KEY_AC_HOME					SDL_Scancode::SDL_SCANCODE_AC_HOME
#define KEY_AC_BACK					SDL_Scancode::SDL_SCANCODE_AC_BACK
#define KEY_AC_FORWARD				SDL_Scancode::SDL_SCANCODE_AC_FORWARD
#define KEY_AC_STOP					SDL_Scancode::SDL_SCANCODE_AC_STOP
#define KEY_AC_REFRESH				SDL_Scancode::SDL_SCANCODE_AC_REFRESH
#define KEY_AC_BOOKMARKS			SDL_Scancode::SDL_SCANCODE_AC_BOOKMARKS

#define KEY_SOFTLEFT				SDL_Scancode::SDL_SCANCODE_SOFTLEFT

#define KEY_SOFTRIGHT				SDL_Scancode::SDL_SCANCODE_SOFTRIGHT

#define KEY_CALL					SDL_Scancode::SDL_SCANCODE_CALL
#define KEY_ENDCALL					SDL_Scancode::SDL_SCANCODE_ENDCALL

#define KEY_RESERVED				SDL_Scancode::SDL_SCANCODE_RESERVED

#define KEY_COUNT					SDL_Scancode::SDL_SCANCODE_COUNT

#define BUTTON_INVALID				SDL_GamepadButton::SDL_GAMEPAD_BUTTON_INVALID
#define BUTTON_SOUTH				SDL_GamepadButton::SDL_GAMEPAD_BUTTON_SOUTH
#define BUTTON_EAST					SDL_GamepadButton::SDL_GAMEPAD_BUTTON_EAST
#define BUTTON_WEST					SDL_GamepadButton::SDL_GAMEPAD_BUTTON_WEST
#define BUTTON_NORTH				SDL_GamepadButton::SDL_GAMEPAD_BUTTON_NORTH
#define BUTTON_BACK					SDL_GamepadButton::SDL_GAMEPAD_BUTTON_BACK
#define BUTTON_GUIDE				SDL_GamepadButton::SDL_GAMEPAD_BUTTON_GUIDE
#define BUTTON_START				SDL_GamepadButton::SDL_GAMEPAD_BUTTON_START
#define BUTTON_LEFT_STICK			SDL_GamepadButton::SDL_GAMEPAD_BUTTON_LEFT_STICK
#define BUTTON_RIGHT_STICK			SDL_GamepadButton::SDL_GAMEPAD_BUTTON_RIGHT_STICK
#define BUTTON_LEFT_SHOULDER		SDL_GamepadButton::SDL_GAMEPAD_BUTTON_LEFT_SHOULDER
#define BUTTON_RIGHT_SHOULDER		SDL_GamepadButton::SDL_GAMEPAD_BUTTON_RIGHT_SHOULDER
#define BUTTON_DPAD_UP				SDL_GamepadButton::SDL_GAMEPAD_BUTTON_DPAD_UP
#define BUTTON_DPAD_DOWN			SDL_GamepadButton::SDL_GAMEPAD_BUTTON_DPAD_DOWN
#define BUTTON_DPAD_LEFT			SDL_GamepadButton::SDL_GAMEPAD_BUTTON_DPAD_LEFT
#define BUTTON_DPAD_RIGHT			SDL_GamepadButton::SDL_GAMEPAD_BUTTON_DPAD_RIGHT
#define BUTTON_MISC1				SDL_GamepadButton::SDL_GAMEPAD_BUTTON_MISC1
#define BUTTON_RIGHT_PADDLE1		SDL_GamepadButton::SDL_GAMEPAD_BUTTON_RIGHT_PADDLE1
#define BUTTON_LEFT_PADDLE1			SDL_GamepadButton::SDL_GAMEPAD_BUTTON_LEFT_PADDLE1
#define BUTTON_RIGHT_PADDLE2		SDL_GamepadButton::SDL_GAMEPAD_BUTTON_RIGHT_PADDLE2
#define BUTTON_LEFT_PADDLE2			SDL_GamepadButton::SDL_GAMEPAD_BUTTON_LEFT_PADDLE2
#define BUTTON_TOUCHPAD				SDL_GamepadButton::SDL_GAMEPAD_BUTTON_TOUCHPAD
#define BUTTON_MISC2				SDL_GamepadButton::SDL_GAMEPAD_BUTTON_MISC2
#define BUTTON_MISC3				SDL_GamepadButton::SDL_GAMEPAD_BUTTON_MISC3
#define BUTTON_MISC4				SDL_GamepadButton::SDL_GAMEPAD_BUTTON_MISC4
#define BUTTON_MISC5				SDL_GamepadButton::SDL_GAMEPAD_BUTTON_MISC5
#define BUTTON_MISC6				SDL_GamepadButton::SDL_GAMEPAD_BUTTON_MISC6
#define BUTTON_COUNT				SDL_GamepadButton::SDL_GAMEPAD_BUTTON_COUNT