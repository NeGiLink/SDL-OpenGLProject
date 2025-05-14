#pragma once
#include <SDL3/SDL.h>
#include <cmath>

//ゲーム内の時間関係の処理を管理するクラス
//主にstaticで使用する
class Time
{
public:
	static void		InitializeDeltaTime();
	static void		UpdateDeltaTime();

	static float	GetFrameRate() { return std::floor(mFrameRate * 10.0f) / 10.0f;; }


	//時間の大きさ
	static float	gTimeScale;
	//timeScaleの影響を受けない経過時間
	static float	gUnscaledDeltaTime;
	//timeScaleの影響を受ける経過時間
	static float	gDeltaTime;
	
	static Uint64	gTicksCount;
private:
	static float	mFrameRate;
};