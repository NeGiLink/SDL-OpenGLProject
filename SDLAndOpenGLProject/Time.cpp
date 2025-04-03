#include "Time.h"

float Time::deltaTime = 0.0f;

Uint64 Time::mTicksCount = 0.0f;

void Time::InitializeDeltaTime()
{
	mTicksCount = SDL_GetTicksNS();
}

void Time::UpdateDeltaTime()
{
	while ((SDL_GetTicksNS() - mTicksCount) < 16'000'000) // 16ms = 16,000,000ns
		;
	deltaTime = (SDL_GetTicksNS() - mTicksCount) / 1'000'000'000.0f;

	// Clamp maximum delta time value
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}

	// Update tick counts (for next frame)
	mTicksCount = SDL_GetTicksNS();
}
