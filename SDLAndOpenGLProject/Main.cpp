#define SDL_MAIN_HANDLED
#include <stdio.h>
#include "WinMain.h"

int main(int argc, char* argv[]) {
	WinMain game;
	bool success = game.Initialize();
	if (success)
	{
		game.RunLoop();
	}
	game.Shutdown();
	return 0;
}