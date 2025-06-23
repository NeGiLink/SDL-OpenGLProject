#pragma once
#include "BaseScene.h"
#include "SoundEventClip.h"
#include "TPSCanvas.h"
#include "Stages01.h"

//スケルタルメッシュなどの人型のキャラクターを生成しているシーン
class DebugScene02 : public BaseScene
{
private:
	// Game-specific code

	class TPSPlayer*				mTPSPlayer;

	Stages01*						mStages01;

	class SpriteComponent*			mCrosshair;

	SoundEventClip					mMusicEvent;

	TPSCanvas*						mTPSCanvas;
public:
									DebugScene02(class GameWinMain* winMain);
	
	bool							Initialize()override;
	
	bool							InputUpdate(const InputState& state)override;

	bool							Update()override;
	
	void							HandleKeyPress(int key)override;

};