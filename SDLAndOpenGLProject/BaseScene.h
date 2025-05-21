#pragma once
#include "Math.h"
#include "WinMain.h"


//シーンの基底クラス
//オブジェクトの更新などをまとめて行う部分になります。
class BaseScene
{
public:
	//コンストラクタ
													BaseScene(class GameWinMain* winMain);
	//初期化
	virtual bool									Initialize();
	//入力更新
	virtual bool									InputUpdate();
	//固定更新
	virtual bool									FixedUpdate();
	//更新
	virtual bool									Update();
	
	virtual void									HandleKeyPress(int key);
	//解放
	void											UnloadData();
	//ゲーム終了時の解放
	void											Shutdown();
	//オブジェクト追加
	void											AddActor(class ActorObject* actor);
	//オブジェクト削除
	void											RemoveActor(class ActorObject* actor);
	//GameWinMainのGetter
	class GameWinMain*								GetWinMain() { return mWinMain; }
	//FontのGetter
	class Font*										GetFont(const string& fileName);
	//Textの読み込み
	void											LoadText(const string& fileName);
	//TextのGetter
	const string&									GetText(const string& key);
	//スケルトンのGetter
	class Skeleton*									GetSkeleton(const string& fileName);
	//アニメーターのGetter
	class Animator*									GetAnimator(const string& fileName, class Animator* animator);
	//AudioSystemのGetter
	class AudioSystem*								GetAudioSystem() { return mAudioSystem; }
	//PhysWorldのGetter
	class PhysWorld*								GetPhysWorld() { return mPhysWorld; }
	//HUDのGetter
	class HUD*										GetHUD() { return mHUD; }
	// Manage UI stack
	const vector<class Canvas*>&					GetUIStack() { return mUIStack; }
	//UIScreenの設定
	void											PushUI(class Canvas* screen);
	//Image配列のGetter
	const vector<class Image*>&						GetImageStack() { return mImageStack; }
	//Imageの追加
	void											PushImage(class Image* screen);
	void											RemoveImage(class Image* screen);
	// Game-specific
	//PlayerオブジェクトのGetter
	class ActorObject*								GetPlayer() { return mPlayer; }
	//CameraのGetter
	class BaseCamera*								GetCamera() { return mMainCamera; }
	//MainCameraの設定
	void											SetMainCamera(class BaseCamera* camera) { mMainCamera = camera; }

protected:

	class GameWinMain*								mWinMain;

	// Track if we're updating actors right now
	bool											mUpdatingActors;

	// All the actors in the game
	vector<class ActorObject*>						mActors;
	vector<class Canvas*>							mUIStack;
	vector<class Image*>							mImageStack;
	// Map for fonts
	std::unordered_map<string, class Font*>			mFonts;
	// Map of loaded skeletons
	std::unordered_map<string, class Skeleton*>		mSkeletons;
	// Map of loaded animations
	std::unordered_map<string, class Animation*>	mAnims;
	std::unordered_map<string, class Animator*>		mAnimators;
	// Map for text localization
	std::unordered_map<string, string>				mText;
	// Any pending actors
	vector<class ActorObject*>						mPendingActors;

	class AudioSystem*								mAudioSystem;
	class PhysWorld*								mPhysWorld;
	class HUD*										mHUD;

	class ActorObject*								mPlayer;

	class BaseCamera*								mMainCamera;

	//SoundEvent									mMusicEvent;
	// 50Hz、Unityと同じ
	const float										mFixed_Delta_Time = 0.02f; 

	float											fixedTimeAccumulator;
};