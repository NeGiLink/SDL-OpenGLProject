#define SDL_MAIN_HANDLED
#define NOMINMAX
#include <windows.h>
#include <stdio.h>
#include "WinMain.h"

int main(int argc, char* argv[]) {
	SetDllDirectoryA("Dll/");
	GameWinMain game;
	bool success = game.Initialize();
	if (success)
	{
		game.RunLoop();
	}
	game.Shutdown();
	return 0;
}