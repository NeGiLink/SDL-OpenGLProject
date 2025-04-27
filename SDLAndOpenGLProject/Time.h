#pragma once
#include <SDL3/SDL.h>
#include <cmath>

class Time
{
public:
	static void InitializeDeltaTime();
	static void UpdateDeltaTime();

	static float GetFrameRate() { return std::floor(frameRate * 10.0f) / 10.0f;; }


	//ŽžŠÔ‚Ì‘å‚«‚³
	static float	timeScale;
	//timeScale‚Ì‰e‹¿‚ðŽó‚¯‚È‚¢Œo‰ßŽžŠÔ
	static float	unscaledDeltaTime;
	//timeScale‚Ì‰e‹¿‚ðŽó‚¯‚éŒo‰ßŽžŠÔ
	static float	deltaTime;
	
	static Uint64	mTicksCount;
private:
	static float	frameRate;
};