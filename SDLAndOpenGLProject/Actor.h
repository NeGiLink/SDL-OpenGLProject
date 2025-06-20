#pragma once
#include "BaseScene.h"
#include "Collider.h"
#include "Rigidbody.h"
#include "Transform.h"

/*
* ===エンジン内部処理/Engine internal processing===
*/

enum ActorTag
{
	None,
	Player,
	Ground,
	Enemy,
	Recovery
};

//全3Dモデルの基底クラス
class ActorObject : public Transform
{
public:
	enum State
	{
		EActive,
		EPaused,
		EDead
	};
protected:
	// Actor's state
	State						mState;

	//オブジェクトのタグ
	ActorTag					mActorTag = ActorTag::None;

	BaseScene*					mGame;

	class Rigidbody*			mRigidbody;

	Collider*					mCollider;
public:
	//コンストラクタ
								ActorObject();
	//デストラクタ
	virtual						~ActorObject();
	// ゲームから一定数で呼び出される更新関数（オーバーライド不可）
	void						FixedUpdate(float deltaTime);
	// Actorに接続されたすべてのコンポーネントを更新します（オーバーライド不可）
	void						FixedUpdateComponents(float deltaTime);
	// 任意のActor固有の更新コード（上書き可能）
	virtual void				FixedUpdateActor(float deltaTime);
	// ゲームから呼び出される更新関数（オーバーライド不可）
	void						Update(float deltaTime);
	// Actorに接続されたすべてのコンポーネントを更新します（オーバーライド不可）
	void						UpdateComponents(float deltaTime);
	// 任意のActor固有の更新コード（上書き可能）
	virtual void				UpdateActor(float deltaTime);
	// ゲームから呼び出されたProcessInput関数（オーバーライドできません）
	void						ProcessInput(const struct InputState& keyState);
	// 任意のActor特有の入力コード（上書き可能）
	virtual void				ActorInput(const struct InputState& keyState);

	// Getters/setters
	State						GetState() const { return mState; }

	void						SetState(State state) { mState = state; }

	virtual ActorTag			GetActorTag() { return mActorTag; }

	void						SetActorTag(ActorTag tag) { mActorTag = tag; }
	
	class BaseScene*			GetGame() { return mGame; }
	class Rigidbody*			GetRigidbody() { return mRigidbody; }

	class Collider*				GetCollider() { return mCollider; }


	//親のアクターのGetter
	//当たった時に呼び出される関数
	virtual void				OnCollisionEnter(ActorObject* target){}
	//当たっている時に呼び出される関数
	virtual void				OnCollisionStay(ActorObject* target){}
	//当たり終わった時に呼び出される関数
	virtual void				OnCollisionExit(ActorObject* target){}
};