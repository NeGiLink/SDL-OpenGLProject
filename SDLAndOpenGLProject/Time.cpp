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

    // unscaledDeltaTime���܂��v�Z
    unscaledDeltaTime = (currentTicks - mTicksCount) / 1'000'000'000.0f;

    // �N�����v (�傫������deltaTime��h��)
    if (unscaledDeltaTime > 0.05f)
    {
        unscaledDeltaTime = 0.05f;
    }

    // timeScale��K�p����deltaTime���쐬
    deltaTime = unscaledDeltaTime * timeScale;

    // �t���[�����[�g���v�Z�i��������unscaled�ł�scaled�ł��D�݁j
    frameRate = 1.0f / unscaledDeltaTime;

    // ���̃t���[���p�Ɍ��݂̎�����ۑ�
    mTicksCount = currentTicks;
}
