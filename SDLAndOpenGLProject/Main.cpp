#define SDL_MAIN_HANDLED
#include <stdio.h>
#include "WinMain.h"

//TODO : プロジェクトを実行している場所
int main(int argc, char* argv[]) 
{
	GameWinMain game;
	bool success = game.Initialize();
	if (success)
	{
		game.RunLoop();
	}
	game.Shutdown();
	return 0;
}