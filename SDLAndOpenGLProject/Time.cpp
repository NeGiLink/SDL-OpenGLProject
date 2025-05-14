#include "Time.h"

float Time::gTimeScale = 1.0f;

float Time::gUnscaledDeltaTime = 0.0f;

float Time::gDeltaTime = 0.0f;

Uint64 Time::gTicksCount = 0.0f;

float Time::mFrameRate = 0.0f;

void Time::InitializeDeltaTime()
{
	gTicksCount = SDL_GetTicksNS();
}

void Time::UpdateDeltaTime()
{
    // 60FPS : 16ms = 16,000,000ns
    // 120FPS : 8.33ms = 8'333'333ns
    while ((SDL_GetTicksNS() - gTicksCount) < 8'333'333)
        ;

    Uint64 currentTicks = SDL_GetTicksNS();

    // unscaledDeltaTimeをまず計算
    gUnscaledDeltaTime = (currentTicks - gTicksCount) / 1'000'000'000.0f;

    // クランプ (大きすぎるdeltaTimeを防ぐ)
    if (gUnscaledDeltaTime > 0.05f)
    {
        gUnscaledDeltaTime = 0.05f;
    }

    // timeScaleを適用してdeltaTimeを作成
    gDeltaTime = gUnscaledDeltaTime * gTimeScale;

    // フレームレートを計算（こっちはunscaledでもscaledでも好み）
    mFrameRate = 1.0f / gUnscaledDeltaTime;

    // 次のフレーム用に現在の時刻を保存
    gTicksCount = currentTicks;
}
