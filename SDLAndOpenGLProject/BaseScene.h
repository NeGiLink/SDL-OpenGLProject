#pragma once
#include "Math.h"
#include "WinMain.h"


//�V�[���̊��N���X
//�I�u�W�F�N�g�̍X�V�Ȃǂ��܂Ƃ߂čs�������ɂȂ�܂��B
class BaseScene
{
public:
	//�R���X�g���N�^
													BaseScene(class GameWinMain* winMain);
	//������
	virtual bool									Initialize();
	//���͍X�V
	virtual bool									InputUpdate();
	//�Œ�X�V
	virtual bool									FixedUpdate();
	//�X�V
	virtual bool									Update();
	
	virtual void									HandleKeyPress(int key);
	//���
	void											UnloadData();
	//�Q�[���I�����̉��
	void											Shutdown();
	//�I�u�W�F�N�g�ǉ�
	void											AddActor(class ActorObject* actor);
	//�I�u�W�F�N�g�폜
	void											RemoveActor(class ActorObject* actor);
	//GameWinMain��Getter
	class GameWinMain*								GetWinMain() { return mWinMain; }
	//Font��Getter
	class Font*										GetFont(const string& fileName);
	//Text�̓ǂݍ���
	void											LoadText(const string& fileName);
	//Text��Getter
	const string&									GetText(const string& key);
	//�X�P���g����Getter
	class Skeleton*									GetSkeleton(const string& fileName);
	//�A�j���[�^�[��Getter
	class Animator*									GetAnimator(const string& fileName, class Animator* animator);
	//AudioSystem��Getter
	class AudioSystem*								GetAudioSystem() { return mAudioSystem; }
	//PhysWorld��Getter
	class PhysWorld*								GetPhysWorld() { return mPhysWorld; }
	//HUD��Getter
	class HUD*										GetHUD() { return mHUD; }
	// Manage UI stack
	const vector<class Canvas*>&					GetUIStack() { return mUIStack; }
	//UIScreen�̐ݒ�
	void											PushUI(class Canvas* screen);
	//Image�z���Getter
	const vector<class Image*>&						GetImageStack() { return mImageStack; }
	//Image�̒ǉ�
	void											PushImage(class Image* screen);
	void											RemoveImage(class Image* screen);
	// Game-specific
	//Player�I�u�W�F�N�g��Getter
	class ActorObject*								GetPlayer() { return mPlayer; }
	//Camera��Getter
	class BaseCamera*								GetCamera() { return mMainCamera; }
	//MainCamera�̐ݒ�
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
	// 50Hz�AUnity�Ɠ���
	const float										mFixed_Delta_Time = 0.02f; 

	float											fixedTimeAccumulator;
};