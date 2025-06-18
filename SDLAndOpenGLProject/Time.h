#pragma once
#include <SDL3/SDL.h>
#include <cmath>
#include "Math.h"

/*
* ===�G���W����������/Engine internal processing===
*/

namespace TimeLayout
{
	// 60FPS : 16ms = 16,000,000ns
	
	// 120FPS : 8.33ms = 8'333'333ns

	constexpr int MIN_FPS = 16000000;

	constexpr int MAX_FPS = 8'333'333;

	constexpr float MAX_DELTATIME = 0.1f;

	constexpr float MIN_DELTATIME = 0.05f;

}

//�Q�[�����̎��Ԋ֌W�̏������Ǘ�����N���X
//���static�Ŏg�p����
class Time
{
public:
	enum FrameRateType
	{
		Frame_60,
		Frame_120,
	};
private:
	static float	mFrameRate;

	static float    mMaxDeltaTime;

	static Uint64   mMaxTicksCount;
public:
	static void		InitializeDeltaTime();

	static void		UpdateDeltaTime();

	static float	GetFrameRate() { return std::floor(mFrameRate * 10.0f) / 10.0f;; }

	static float	GetMaxDeltaTime() { return mMaxDeltaTime; }

	static void		SetMaxDeltaTime(float time);

	static Uint64   GetMaxTicksCount() { return mMaxTicksCount; }

	static void     SetMaxTicksCount(FrameRateType type);

	//���Ԃ̑傫��
	static float	gTimeScale;
	//timeScale�̉e�����󂯂Ȃ��o�ߎ���
	static float	gUnscaledDeltaTime;
	//timeScale�̉e�����󂯂�o�ߎ���
	static float	gDeltaTime;
	
	static Uint64	gTicksCount;
};