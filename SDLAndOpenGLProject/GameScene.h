#pragma once
#include <unordered_map>
#include <string>
#include <vector>
#include "Math.h"
#include "SoundEvent.h"
#include <SDL3/SDL.h>
#include <stdint.h>

class GameScene
{
public:
	GameScene();
	bool Setup();
	void RunLoop();
	void Shutdown();
private:
	bool Initialize();
	bool Update();
	bool Render();
	bool Release();
};

