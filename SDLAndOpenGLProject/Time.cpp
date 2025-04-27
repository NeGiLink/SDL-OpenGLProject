#include "Time.h"

float Time::timeScale = 1.0f;

float Time::unscaledDeltaTime = 0.0f;

float Time::deltaTime = 0.0f;

Uint64 Time::mTicksCount = 0.0f;

float Time::frameRate = 0.0f;

void Time::InitializeDeltaTime()
{
	mTicksCount = SDL_GetTicksNS();
}

void Time::UpdateDeltaTime()
{
    // 60FPS : 16ms = 16,000,000ns
    // 120FPS : 8.33ms = 8'333'333ns
    while ((SDL_GetTicksNS() - mTicksCount) < 8'333'333)
        ;

    Uint64 currentTicks = SDL_GetTicksNS();

    // unscaledDeltaTimeをまず計算
    unscaledDeltaTime = (currentTicks - mTicksCount) / 1'000'000'000.0f;

    // クランプ (大きすぎるdeltaTimeを防ぐ)
    if (unscaledDeltaTime > 0.05f)
    {
        unscaledDeltaTime = 0.05f;
    }

    // timeScaleを適用してdeltaTimeを作成
    deltaTime = unscaledDeltaTime * timeScale;

    // フレームレートを計算（こっちはunscaledでもscaledでも好み）
    frameRate = 1.0f / unscaledDeltaTime;

    // 次のフレーム用に現在の時刻を保存
    mTicksCount = currentTicks;
}
