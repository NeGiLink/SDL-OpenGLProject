#pragma once
#include "BaseScene.h"
#include "SoundEventClip.h"

//�X�P���^�����b�V���Ȃǂ̐l�^�̃L�����N�^�[�𐶐����Ă���V�[��
class DebugScene02 : public BaseScene
{
private:
	// Game-specific code

	class SkeletonMeshActor*		mTestCharacter;

	class TPSPlayer*				mTPSPlayer;

	class SkeletonMeshActor*		mSmallCharacter;

	class MeshActor*				mDebugStage1;

	class MeshActor*				mDebugStage2;

	class SpriteComponent*			mCrosshair;

	SoundEventClip					mMusicEvent;

	//�t���[�����[�g�\���e�L�X�g
	class Text*						mFrameRateText;

	class Text*						mPoseButtonText;

	class Text*						mSceneLoadButtonText;

	//***�A�j���[�V�����Đ��{�^���e�L�X�g***
	class Text*						mSceneNameText;

	class Text*						mTPoseButtonText;

	class Text*						mIdlePoseButtonText;

	class Text*						mRunPoseButtonText;

	class Text*						mJumpPoseButtonText;

	class Text*						mCapoeiraPoseButtonText;
public:
									DebugScene02(class GameWinMain* winMain);
	
	bool							Initialize()override;
	
	bool							InputUpdate(const InputState& state)override;

	bool							Update()override;
	
	void							HandleKeyPress(int key)override;

};