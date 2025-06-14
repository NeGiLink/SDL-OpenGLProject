#pragma once
#include "SDOpenLib.h"

enum GameState
{
	GamePlay,
	TimeStop,
	GameEnd
};

class GameStateClass 
{
public:
	static void			SetGameState(GameState state) { mGameState = state; }
	static GameState	mGameState;
	static bool			mGameEventFrag;
};
//ゲームの描画処理管理クラス
//主にRenderernなどの画面の構成を管理しているクラス
class GameWinMain
{
private:
	//ゲーム内の全ての描画を行うクラス
	void				Render();
	//シーン遷移時の解放処理
	void				UnloadData();

	class Renderer*		mRenderer;

	//ゲーム内処理
	GameApp*			mGameApp;
public:
						GameWinMain();
	//初期化
	bool				Initialize();
	//ゲーム処理
	void				RunLoop();
	//ゲーム終了処理
	void				Shutdown();
	//Rendererの取得
	class Renderer*		GetRenderer() { return mRenderer; }
};