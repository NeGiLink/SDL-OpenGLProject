#pragma once
#include "Actor.h"
#include <string>

//テスト用に3Dモデルを読み込んでいるクラス
//名前はどのモデル化分かりやすくするためにこの名前にしました。
class YBotActor : public ActorObject
{
public:
	YBotActor(class BaseScene* game);
	void ActorInput(const struct InputState& keys) override;
	void UpdateActor(float deltaTime) override;
private:
	enum State
	{
		Idle,
		Run,
		Jump,
		Capoeira,
		TPose
	};

	class SkeletalMeshRenderer*		mMeshComp;

	class Animator*					animator;

	class Sword*					mSword;

	std::string						animatorName = "YBot";
};

