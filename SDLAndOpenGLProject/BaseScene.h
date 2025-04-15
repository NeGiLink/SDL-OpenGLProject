#pragma once
#include <unordered_map>
#include <string>
#include <vector>
#include "Math.h"
#include "SoundEvent.h"
#include <SDL3/SDL.h>
#include <stdint.h>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <rapidjson/document.h>
#include "WinMain.h"

//シーンの基底クラス
//オブジェクトの更新などをまとめて行う部分になります。
class BaseScene
{
public:
	BaseScene(class WinMain* winMain);

	bool Setup();

	void ProcessInput();
	
	void UpdateGame();
	
	void UnloadData();
	
	void Shutdown();

	void AddActor(class ActorObject* actor);
	
	void RemoveActor(class ActorObject* actor);

	class WinMain* GetWinMain() { return mWinMain; }

	class Font* GetFont(const std::string& fileName);

	void LoadText(const std::string& fileName);
	
	const std::string& GetText(const std::string& key);
	
	const std::string& GetFreeText(const std::string& key);

	class Skeleton* GetSkeleton(const std::string& fileName);

	class Animator* GetAnimator(const std::string& fileName, class Animator* animator);

	class AudioSystem* GetAudioSystem() { return mAudioSystem; }
	
	class PhysWorld* GetPhysWorld() { return mPhysWorld; }
	
	class HUD* GetHUD() { return mHUD; }
	// Manage UI stack
	const std::vector<class UIScreen*>& GetUIStack() { return mUIStack; }
	
	void PushUI(class UIScreen* screen);

	const std::vector<class Image*>& GetImageStack() { return mImageStack; }
	
	void PushImage(class Image* screen);

	// Game-specific
	void AddPlane(class PlaneActor* plane);
	
	void RemovePlane(class PlaneActor* plane);
	
	std::vector<class PlaneActor*>& GetPlanes() { return mPlanes; }

	class ActorObject* GetPlayer() { return mPlayer; }
protected:

	class WinMain*										mWinMain;

	// Track if we're updating actors right now
	bool												mUpdatingActors;

	// All the actors in the game
	std::vector<class ActorObject*>						mActors;
	std::vector<class UIScreen*>						mUIStack;
	std::vector<class Image*>							mImageStack;
	// Map for fonts
	std::unordered_map<std::string, class Font*>		mFonts;
	// Map of loaded skeletons
	std::unordered_map<std::string, class Skeleton*>	mSkeletons;
	// Map of loaded animations
	std::unordered_map<std::string, class Animation*>	mAnims;
	std::unordered_map<std::string, class Animator*>	mAnimators;
	// Map for text localization
	std::unordered_map<std::string, std::string>		mText;
	// Any pending actors
	std::vector<class ActorObject*>						mPendingActors;

	std::vector<class PlaneActor*>						mPlanes;

	class AudioSystem*									mAudioSystem;
	class PhysWorld*									mPhysWorld;
	class HUD*											mHUD;

	class ActorObject*									mPlayer;

	SoundEvent											mMusicEvent;
};