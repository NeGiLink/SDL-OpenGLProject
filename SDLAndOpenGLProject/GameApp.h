#pragma once
#include "SDL3.h"
#include "Renderer.h"

//前方宣言
class BaseScene;
class TitleScene;
class DebugScene01;
class DebugScene02;
class GameWinMain;


//ゲーム全体の処理を行うクラス
//ここにゲームに必要な処理を書いていく想定で制作しました。
class GameApp
{
private:
	//現在の有効なシーン
	static BaseScene*		mActiveScene;
	TitleScene*				mTitleScene;
	//シーン01
	DebugScene01*			mDebugScene01;
	//シーン02
	DebugScene02*			mDebugScene02;
	//描画管理クラス
	GameWinMain*			mWinMain;
public:
							GameApp(GameWinMain* main);
	//初期化
	bool					Initialize();
	//入力処理
	bool					ProcessInput();
	//シーンのロード処理
	bool					LoadUpdate();
	//更新処理
	bool					Update();
	//解放
	bool					Release();
	//現在有効なシーンをstaticで取得
	static BaseScene*		GetActiveScene() { return mActiveScene; }
};