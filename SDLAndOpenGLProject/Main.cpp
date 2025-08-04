
#include "WinMain.h"
#include <SDL3/SDL.h>

#define DISABLE_DEBUG_NEW // 一時的に無効にして
#include "Debug_memory.h"
#undef DISABLE_DEBUG_NEW   // すぐに解除


//TODO : プロジェクトを実行している場所
//構成マネージャーがDebugなら
#ifdef _DEBUG
int main(int argc, char* argv[])
// プロジェクトの実行場所がReleaseなら
#else
#define SDL_MAIN_HANDLED
#include <windows.h>
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
#endif
{
	// メモリリーク検出を有効にする
	EnableMemoryLeakCheck(); 
	GameWinMain game;
	bool success = game.Initialize();
	if (success)
	{
		game.RunLoop();
	}
	game.Shutdown();
	return 0;
}