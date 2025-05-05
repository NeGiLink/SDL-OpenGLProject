#pragma once
#include "StandardLibrary.h"
#include "Math.h"
#include "Collision.h"
#include "Component.h"
#include "Actor.h"
#include "BaseScene.h"
#include "PhysWorld.h"

//オブジェクトにコンポーネントして使うRigidbody
class Rigidbody : public Component
{
public:
	Rigidbody(class ActorObject* owner, int updateOrder = 100);
	//FixedUpdateで呼び出す
	void	FixedUpdate(float deltaTime)override;

	//Getter
	//重力フラグの参照
	bool	IsUseGravity() { return mUseGravity; }
	//力を加える関数
	void	AddForce(Vector3 velocity);
	//mVelocityのGetter
	Vector3 GetVelocity() { return mVelocity; }
	//Setter
	//重力フラグの切り替え
	void	SetUseGravity(bool active) { mUseGravity = active; }
	//mVelocityのSetter
	void	SetVelocity(Vector3 velocity) { mVelocity = velocity; }
private:
	//重力フラグ
	bool	mUseGravity;
	//重力スケーリング
	float	mGravityScale;
	//質量(1.0f = 1kg)
	float	mMass;
	//移動量
	Vector3 mVelocity;
	//加える分の力の変数
	Vector3 mForces = Vector3::Zero;
};

