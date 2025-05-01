#pragma once
#include "Math.h"
#include "WinMain.h"
#include "MeshFilePath.h"

//シーンの基底クラス
//オブジェクトの更新などをまとめて行う部分になります。
class BaseScene
{
public:
	BaseScene(class GameWinMain* winMain);
	

	virtual bool Initialize();

	virtual bool InputUpdate();

	virtual bool Update();

	virtual void HandleKeyPress(int key);

	void UnloadData();
	
	void Shutdown();


	void AddActor(class ActorObject* actor);
	
	void RemoveActor(class ActorObject* actor);

	class GameWinMain* GetWinMain() { return mWinMain; }

	class Font* GetFont(const string& fileName);

	void LoadText(const string& fileName);
	
	const string& GetText(const string& key);
	
	const string& GetFreeText(const string& key);

	class Skeleton* GetSkeleton(const string& fileName);

	class Animator* GetAnimator(const string& fileName, class Animator* animator);

	class AudioSystem* GetAudioSystem() { return mAudioSystem; }
	
	class PhysWorld* GetPhysWorld() { return mPhysWorld; }
	
	class HUD* GetHUD() { return mHUD; }
	// Manage UI stack
	const vector<class UIScreen*>& GetUIStack() { return mUIStack; }
	
	void PushUI(class UIScreen* screen);

	const vector<class Image*>& GetImageStack() { return mImageStack; }
	
	void PushImage(class Image* screen);

	// Game-specific
	void AddPlane(class PlaneActor* plane);
	
	void RemovePlane(class PlaneActor* plane);
	
	vector<class PlaneActor*>& GetPlanes() { return mPlanes; }

	class ActorObject* GetPlayer() { return mPlayer; }
protected:

	class GameWinMain*										mWinMain;

	// Track if we're updating actors right now
	bool												mUpdatingActors;

	// All the actors in the game
	vector<class ActorObject*>						mActors;
	vector<class UIScreen*>						mUIStack;
	vector<class Image*>							mImageStack;
	// Map for fonts
	std::unordered_map<string, class Font*>		mFonts;
	// Map of loaded skeletons
	std::unordered_map<string, class Skeleton*>	mSkeletons;
	// Map of loaded animations
	std::unordered_map<string, class Animation*>	mAnims;
	std::unordered_map<string, class Animator*>	mAnimators;
	// Map for text localization
	std::unordered_map<string, string>		mText;
	// Any pending actors
	vector<class ActorObject*>						mPendingActors;

	vector<class PlaneActor*>						mPlanes;

	class AudioSystem*									mAudioSystem;
	class PhysWorld*									mPhysWorld;
	class HUD*											mHUD;

	class ActorObject*									mPlayer;

	//SoundEvent											mMusicEvent;
};