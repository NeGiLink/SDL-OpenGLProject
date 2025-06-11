#include "Time.h"

float Time::mMaxDeltaTime = 0.05f;

float Time::mFrameRate = 0.0f;

Uint64 Time::mMaxTicksCount = TimeLayout::MAX_FPS;

float Time::gTimeScale = 1.0f;

float Time::gUnscaledDeltaTime = 0.0f;

float Time::gDeltaTime = 0.0f;

Uint64 Time::gTicksCount = 0.0f;


void Time::InitializeDeltaTime()
{
	gTicksCount = SDL_GetTicksNS();
}

void Time::UpdateDeltaTime()
{
    // 60FPS : 16ms = 16,000,000ns
    // 120FPS : 8.33ms = 8'333'333ns
    while ((SDL_GetTicksNS() - gTicksCount) < mMaxTicksCount)
        ;

    Uint64 currentTicks = SDL_GetTicksNS();

    // unscaledDeltaTime���܂��v�Z
    gUnscaledDeltaTime = (currentTicks - gTicksCount) / 1'000'000'000.0f;

    // �N�����v (�傫������deltaTime��h��)
    if (gUnscaledDeltaTime > mMaxDeltaTime)
    {
        gUnscaledDeltaTime = mMaxDeltaTime;
    }

    // timeScale��K�p����deltaTime���쐬
    gDeltaTime = gUnscaledDeltaTime * gTimeScale;

    // �t���[�����[�g���v�Z�i��������unscaled�ł�scaled�ł��D�݁j
    mFrameRate = 1.0f / gUnscaledDeltaTime;

    // ���̃t���[���p�Ɍ��݂̎�����ۑ�
    gTicksCount = currentTicks;
}

void Time::SetMaxDeltaTime(float time)
{
    float result = Math::Clamp(time, TimeLayout::MIN_DELTATIME, TimeLayout::MAX_DELTATIME);
    mMaxDeltaTime = result;
}

void Time::SetMaxTicksCount(FrameRateType type)
{
    switch (type)
    {
    case Frame_60:
        mMaxTicksCount = TimeLayout::MIN_FPS;
        break;
    case Frame_120:
        mMaxTicksCount = TimeLayout::MAX_FPS;
        break;
    }
}
