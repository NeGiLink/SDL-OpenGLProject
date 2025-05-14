#pragma once
#include <SDL3/SDL.h>
#include <cmath>

//�Q�[�����̎��Ԋ֌W�̏������Ǘ�����N���X
//���static�Ŏg�p����
class Time
{
public:
	static void		InitializeDeltaTime();
	static void		UpdateDeltaTime();

	static float	GetFrameRate() { return std::floor(mFrameRate * 10.0f) / 10.0f;; }


	//���Ԃ̑傫��
	static float	gTimeScale;
	//timeScale�̉e�����󂯂Ȃ��o�ߎ���
	static float	gUnscaledDeltaTime;
	//timeScale�̉e�����󂯂�o�ߎ���
	static float	gDeltaTime;
	
	static Uint64	gTicksCount;
private:
	static float	mFrameRate;
};