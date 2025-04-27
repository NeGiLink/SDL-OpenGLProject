#pragma once
#include <SDL3/SDL.h>
#include <cmath>

class Time
{
public:
	static void InitializeDeltaTime();
	static void UpdateDeltaTime();

	static float GetFrameRate() { return std::floor(frameRate * 10.0f) / 10.0f;; }


	//���Ԃ̑傫��
	static float	timeScale;
	//timeScale�̉e�����󂯂Ȃ��o�ߎ���
	static float	unscaledDeltaTime;
	//timeScale�̉e�����󂯂�o�ߎ���
	static float	deltaTime;
	
	static Uint64	mTicksCount;
private:
	static float	frameRate;
};