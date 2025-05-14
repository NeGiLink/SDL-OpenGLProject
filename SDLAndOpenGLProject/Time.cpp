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

    // unscaledDeltaTime���܂��v�Z
    gUnscaledDeltaTime = (currentTicks - gTicksCount) / 1'000'000'000.0f;

    // �N�����v (�傫������deltaTime��h��)
    if (gUnscaledDeltaTime > 0.05f)
    {
        gUnscaledDeltaTime = 0.05f;
    }

    // timeScale��K�p����deltaTime���쐬
    gDeltaTime = gUnscaledDeltaTime * gTimeScale;

    // �t���[�����[�g���v�Z�i��������unscaled�ł�scaled�ł��D�݁j
    mFrameRate = 1.0f / gUnscaledDeltaTime;

    // ���̃t���[���p�Ɍ��݂̎�����ۑ�
    gTicksCount = currentTicks;
}
