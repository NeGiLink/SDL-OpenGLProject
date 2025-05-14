#pragma once
#include "Actor.h"
#include "Mesh.h"
#include "SkeletalMeshRenderer.h"
#include "Animator.h"
#include "BoxCollider.h"
#include "Sword.h"
#include "FollowCamera.h"
#include "FollowObjectMovement.h"

//テスト用に3Dモデルを読み込んでいるクラス
//名前はどのモデル化分かりやすくするためにこの名前にしました。
class YBotActor : public ActorObject
{
public:
									YBotActor();

	void							UpdateActor(float deltaTime)override;

	void							ActorInput(const struct InputState& keys) override;

	void							OnCollisionEnter(class ActorObject* target) override;

	void							OnCollisionExit(class ActorObject* target) override;
private:
	enum State
	{
		Idle,
		Run,
		Jump,
		RunJump,
		Capoeira,
		TPose
	};

	class SkeletalMeshRenderer*		mSkeletonMesh;

	class Animator*					animator;

	class Sword*					mSword;

	string							animatorName = "YBot";

	class FollowCamera*				mFollowCamera;

	class FollowObjectMovement*		mMovement;

	class BoxCollider*				mBoxComp;
	
};