#pragma once

#include <vector>
#include "Math.h"
#include <cstdint>
#include "CollisionActor.h"

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

	ActorObject(class BaseScene* game);
	virtual ~ActorObject();

	// ゲームから呼び出される更新関数（オーバーライド不可）
	void Update(float deltaTime);
	// Actorに接続されたすべてのコンポーネントを更新します（オーバーライド不可）
	void UpdateComponents(float deltaTime);
	// 任意のActor固有の更新コード（上書き可能）
	virtual void UpdateActor(float deltaTime);

	// ゲームから呼び出されたProcessInput関数（オーバーライドできません）
	void ProcessInput(const struct InputState& keyState);
	// 任意のActor特有の入力コード（上書き可能）
	virtual void ActorInput(const struct InputState& keyState);

	// Getters/setters
	const Vector3& GetPosition() const { return mPosition; }

	void SetPosition(const Vector3& pos) 
	{
		mPosition = pos; 
		mRecomputeWorldTransform = true; 
	}

	void AddPosition(const Vector3& pos) 
	{
		mPosition += pos;
		mRecomputeWorldTransform = true;
	}
	// Getters/setters
	Vector3 GetScale() const { return mScale; }
	
	void SetScale(Vector3 scale) { mScale = scale;  mRecomputeWorldTransform = true; }
	
	void SetScale(float scale) { mScale = Vector3(scale,scale,scale);  mRecomputeWorldTransform = true; }
	// Getters/setters
	const Quaternion& GetRotation() const { return mRotation; }

	void SetRotationAmountX(float rot) { mRotationAmountX = rot; }
	void SetRotationAmountY(float rot) { mRotationAmountY = rot; }
	void SetRotationAmountZ(float rot) { mRotationAmountZ = rot; }
	
	void SetRotation(const Quaternion& rotation) { mRotation = rotation;  mRecomputeWorldTransform = true; }
	
	void AddRotation(const Quaternion& rotation) { mRotation = rotation;  mRecomputeWorldTransform = true; }

	void ComputeWorldTransform();

	void LocalBonePositionUpdateActor(Matrix4 boneMatrix, const class Matrix4& parentActor);
	
	const Matrix4& GetWorldTransform() const { return mWorldTransform; }

	Vector3 GetForward() const { return Vector3::Transform(Vector3::UnitZ, mRotation); }
	
	Vector3 GetRight() const { return Vector3::Transform(Vector3::UnitX, mRotation); }

	Vector3 GetUp() const { return Vector3::Transform(Vector3::UnitY, mRotation); }

	void RotateToNewForward(const Vector3& forward);

	// Getters/setters
	State GetState() const { return mState; }
	
	void SetState(State state) { mState = state; }

	class BaseScene* GetGame() { return mGame; }


	// Add/remove components
	void AddComponent(class Component* component);
	
	void RemoveComponent(class Component* component);
	//子オブジェクトを追加
	void AddChildActor(class ActorObject* actor);
	
	void RemoveChildActor(class ActorObject* actor);
	
	const class ActorObject* GetChildActor(class ActorObject* actor);
	//子オブジェクトの座標更新
	void SetActive() { mRecomputeWorldTransform = true; }
	
	void SetParentActor(class ActorObject* parent) { mParentActor = parent; }


	//当たった時に呼び出される関数
	virtual void OnCollisionEnter(class ActorObject* target){}
	//当たっている時に呼び出される関数
	virtual void OnCollisionStay(class ActorObject* target){}
	//当たり終わった時に呼び出される関数
	virtual void OnCollisionExit(class ActorObject* target){}
private:
	// Transform
	Matrix4		mWorldTransform;
protected:
	// Actor's state
	State							mState;

	Vector3							mPosition;

	Quaternion						mRotation;

	//X、Y、Z軸の回転量
	float							mRotationAmountX;
	float							mRotationAmountY;
	float							mRotationAmountZ;

	Vector3							mScale;

	bool							mRecomputeWorldTransform;

	std::vector<class Component*>	mComponents;
	//親オブジェクト
	class ActorObject*				mParentActor;
	//子オブジェクトの配列
	std::vector<class ActorObject*> mChildActor;

	class BaseScene*				mGame;
};