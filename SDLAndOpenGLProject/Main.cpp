#define SDL_MAIN_HANDLED
#include <stdio.h>
#include "WinMain.h"

//TODO : �v���W�F�N�g�����s���Ă���ꏊ
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