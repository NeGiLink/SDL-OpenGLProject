#define DISABLE_DEBUG_NEW // 一時的に無効にして
#include "Debug_memory.h"
#undef DISABLE_DEBUG_NEW   // すぐに解除
#define SDL_MAIN_HANDLED
#include "WinMain.h"

//TODO : プロジェクトを実行している場所
int main(int argc, char* argv[]) 
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