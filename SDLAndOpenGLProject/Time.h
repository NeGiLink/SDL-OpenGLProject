#pragma once
#include <SDL3/SDL.h>

class Time
{
public:
	static void InitializeDeltaTime();
	static void UpdateDeltaTime();

	static float deltaTime;
	static Uint64 mTicksCount;
};