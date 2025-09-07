#pragma once
#include "GameWinMain.h"

/*
* ===エンジン内部処理/Engine internal processing===
*/

//前方宣言
class ActorObject;
class Canvas;
class Image;
class Font;
class Skeleton;
class DirectionalLightActor;
class BaseCamera;
class Text;

//シーンの基底クラス
//オブジェクトの更新などをまとめて行う部分になります。
// シーンごとに継承して使用します。
class BaseScene
{
public:
	enum MouseMode
	{
		Relative, // 相対モード
		Absolute  // 絶対モード
	};
protected:

	GameWinMain*							mWinMain;

	AudioSystem*							mAudioSystem;

	PhysWorld*								mPhysWorld;
	// Track if we're updating actors right now
	bool									mUpdatingActors;

	// All the actors in the game
	vector<ActorObject*>					mActors;
	vector<Canvas*>							mCanvasStack;
	vector<Image*>							mImageStack;
	vector<Image*>							mDebugImageStack;
	// Map for fonts
	std::unordered_map<string, Font*>		mFonts;
	// Map of loaded skeletons
	std::unordered_map<string, Skeleton*>	mSkeletons;
	// Any pending actors
	vector<ActorObject*>					mPendingActors;


	ActorObject*							mPlayer;

	DirectionalLightActor*					mDirectionalLightActor;

	BaseCamera*								mMainCamera;

	// 50Hz、Unityと同じ
	const float								mFixed_Delta_Time = 0.02f;

	float									mFixedTimeAccumulator;

	//***デバッグ機能***
	//フレームレート表示テキスト
	Text*									mFrameRateText;
public:
	//コンストラクタ
											BaseScene(GameWinMain* winMain);
	//初期化
	virtual bool							Initialize();
	//入力更新
	virtual bool							InputUpdate(const InputState& state);
	//固定更新
	virtual bool							FixedUpdate();
	//更新
	virtual bool							Update();
	//解放
	void									UnloadData();
	//ゲーム終了時の解放
	void									Shutdown();

	void									SetMouseMode(MouseMode mode);

	void									LoadSkyBoxTexture(string file);

	vector<class ActorObject*>&				GetActors() { return mActors; }
	//オブジェクト追加
	void									AddActor(ActorObject* actor);
	//オブジェクト削除
	void									RemoveActor(ActorObject* actor);

	template<typename T>
	vector<ActorObject*>					SelectAllActorComponent();

	//GameWinMainのGetter
	GameWinMain*							GetWinMain() { return mWinMain; }
	//FontのGetter
	Font*									GetFont(const string& fileName);
	//スケルトンのGetter
	Skeleton*								GetSkeleton(const string& fileName);
	//AudioSystemのGetter
	AudioSystem*							GetAudioSystem() { return mAudioSystem; }
	//PhysWorldのGetter
	PhysWorld*								GetPhysWorld() { return mPhysWorld; }

	// Manage UI stack
	const vector<Canvas*>&					GetUIStack() { return mCanvasStack; }
	//UIScreenの設定
	void									PushUI(Canvas* screen);
	//Image配列のGetter
	const vector<Image*>&					GetImageStack() { return mImageStack; }
	const vector<Image*>&					GetDebugImageStack() { return mDebugImageStack; }
	//Imageの追加
	void									PushImage(Image* screen);
	void									RemoveImage(Image* screen);
	//DebugImageの追加
	void									PushDebugImage(Image* screen);
	void									RemoveDebugImage(Image* screen);
	// Game-specific
	//PlayerオブジェクトのGetter
	ActorObject*							GetPlayer() { return mPlayer; }
	//環境光の設定
	DirectionalLightActor*					GetDirectionalLightActor() { return mDirectionalLightActor; }
	//CameraのGetter
	BaseCamera*								GetCamera() { return mMainCamera; }
	//MainCameraの設定
	void									SetMainCamera(BaseCamera* camera) { mMainCamera = camera; }
};

template<typename T>
inline vector<ActorObject*> BaseScene::SelectAllActorComponent()
{
	std::vector<ActorObject*> result;

	for (auto* actor : mActors)
	{
		for (auto* component : actor->GetComponents())
		{
			if (dynamic_cast<T*>(component)) // T型のComponentがあるか
			{
				result.push_back(actor);
				break; // 一つでも見つかればそのオブジェクトは対象になる
			}
		}
	}

	return result;
}

#define Release_Function  0
#define Debug_Function  1