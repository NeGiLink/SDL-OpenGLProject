#pragma once
#include "Actor.h"
#include "Mesh.h"
#include "SkeletalMeshRenderer.h"
#include "Animator.h"
#include "BoxCollider.h"
#include "Sword.h"

//テスト用に3Dモデルを読み込んでいるクラス
//名前はどのモデル化分かりやすくするためにこの名前にしました。
class YBotActor : public ActorObject
{
public:
	YBotActor();
	void ActorInput(const struct InputState& keys) override;
private:
	enum State
	{
		Idle,
		Run,
		Jump,
		Capoeira,
		TPose
	};

	class SkeletalMeshRenderer*		mSkeletonMesh;

	class Animator*					animator;

	class Sword*					mSword;

	string							animatorName = "YBot";
	
};

