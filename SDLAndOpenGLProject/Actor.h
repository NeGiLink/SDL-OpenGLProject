#pragma once
#include "Math.h"
#include "CollisionActor.h"
#include "BaseScene.h"
#include "Component.h"
#include "Collider.h"
#include "Rigidbody.h"

enum ActorTag
{
	None,
	Player,
	Ground
};

//全3Dモデルの基底クラス
//UnityのTransformに近い情報を持っている
class ActorObject
{
public:
	enum State
	{
		EActive,
		EPaused,
		EDead
	};
	//コンストラクタ
	ActorObject();
	//デストラクタ
	virtual ~ActorObject();
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


	const Matrix4&				GetWorldTransform() const { return mWorldTransform; }

	void						SetWorldTransform(Matrix4 mat) { mWorldTransform = mat; }

	const Matrix4&				GetLocalTransform() const { return mModelTransform; }

	Vector3						GetForward() const { return Vector3::Transform(Vector3::UnitZ, mLocalRotation); }

	Vector3						GetRight() const { return Vector3::Transform(Vector3::UnitX, mLocalRotation); }

	Vector3						GetUp() const { return Vector3::Transform(Vector3::UnitY, mLocalRotation); }

	void						RotateToNewForward(const Vector3& forward);

	// Getters/setters
	State						GetState() const { return mState; }

	void						SetState(State state) { mState = state; }

	const Vector3&				GetPosition() const		{ return mPosition; }

	const Quaternion&			GetRotation() const	{ return mRotation; }

	const Vector3&				GetScale() const			{ return mScale; }

	// PositionのGetters/setters
	const Vector3&				GetLocalPosition() const { return mLocalPosition; }

	void						SetPosition(const Vector3& pos) 
	{
		mLocalPosition = pos; 
		mRecomputeWorldTransform = true; 
	}
	//Positionを加算で足す関数
	void						AddPosition(const Vector3& pos) 
	{
		mLocalPosition += pos;
		mRecomputeWorldTransform = true;
	}
	//mPositionOffsetに加算する関数
	void						AddPositionOffset(const Vector3& pos) 
	{
		mPositionOffset += pos;
	}
	// ScaleのGetters/setters
	Vector3						GetLocalScale() const { return mLocalScale; }
	// 1 Ver
	void						SetScale(Vector3 scale) { mLocalScale = scale;  mRecomputeWorldTransform = true; }
	// 2 Ver
	void						SetScale(float scale) { mLocalScale = Vector3(scale,scale,scale);  mRecomputeWorldTransform = true; }
	// RotationのGetters/setters
	const Quaternion&			GetLocalRotation() const 
	{
		return mLocalRotation; 
	}

	void						SetRotation(const Quaternion& rotation) { mLocalRotation = rotation;  mRecomputeWorldTransform = true; }
	
	void						AddRotation(const Quaternion& rotation) { mLocalRotation = rotation;  mRecomputeWorldTransform = true; }
	
	//軸別の回転量のGetters/setters
	float						GetRotationAmountX() { return mRotationAmountX; }
	
	float						GetRotationAmountY() { return mRotationAmountY; }
	
	float						GetRotationAmountZ() { return mRotationAmountZ; }

	void						SetRotationAmountX(float rot) { mRotationAmountX = rot; }
	
	void						SetRotationAmountY(float rot) { mRotationAmountY = rot; }
	
	void						SetRotationAmountZ(float rot) { mRotationAmountZ = rot; }
	
	//ワールド座標の更新		
	virtual void				ComputeWorldTransform(const class Matrix4* parentMatrix);

	void						LocalBonePositionUpdateActor(Matrix4 boneMatrix, const class Matrix4& parentActor);


	//***子オブジェクト関係の処理***
	class ActorObject*			GetParentActor() { return mParentActor; }
	
	const class ActorObject*	GetChildActor(class ActorObject* actor);

	// Add/remove components
	void						AddComponent(class Component* component);
	
	void						RemoveComponent(class Component* component);
	//子オブジェクトを追加
	void						AddChildActor(class ActorObject* actor);
	
	void						RemoveChildActor(class ActorObject* actor);
	
	
	void						AddParentActor(class ActorObject* parent);

	void						RemoveParentActor();

	//子オブジェクトの座標更新
	void						SetActive() { mRecomputeWorldTransform = true; }

	virtual ActorTag			GetActorTag() { return mActorTag; }

	void						SetActorTag(ActorTag tag) { mActorTag = tag; }
	
	class BaseScene*			GetGame() { return mGame; }

	class Rigidbody* GetRigidbody() { return mRigidbody; }

	class Collider* GetCollider() { return mCollider; }

	//親のアクターのGetter

	//当たった時に呼び出される関数
	virtual void				OnCollisionEnter(class ActorObject* target){}
	//当たっている時に呼び出される関数
	virtual void				OnCollisionStay(class ActorObject* target){}
	//当たり終わった時に呼び出される関数
	virtual void				OnCollisionExit(class ActorObject* target){}
protected:
	// World Transform
	Matrix4							mWorldTransform;
	//Model Transform
	Matrix4							mModelTransform;
	// Actor's state
	State							mState;

	//ワールド座標、回転、スケーリング
	Vector3							mPosition;

	Quaternion						mRotation;

	Vector3							mScale;

	//ローカル座標、回転、スケーリング
	Vector3							mLocalPosition;

	Vector3							mPositionOffset;

	Quaternion						mLocalRotation;

	//X、Y、Z軸の回転量
	float							mRotationAmountX;
	float							mRotationAmountY;
	float							mRotationAmountZ;

	Vector3							mLocalScale;

	bool							mRecomputeWorldTransform;

	vector<class Component*>	mComponents;
	//親オブジェクト
	class ActorObject*				mParentActor;
	//子オブジェクトの配列
	vector<class ActorObject*> mChildActor;
	//オブジェクトのタグ
	ActorTag						mActorTag = ActorTag::None;

	class BaseScene*				mGame;

	class Rigidbody*				mRigidbody;

	class Collider*					mCollider;
};