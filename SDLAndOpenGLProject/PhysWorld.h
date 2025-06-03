#pragma once
#include "StandardLibrary.h"
#include "Math.h"
#include "Collision.h"

//書籍部分を改造したファイル
//すべてのオブジェクトの衝突判定を管理しているクラス
//Unityの当たり判定の衝突判定部分みたいな機能
class PhysWorld
{
public:
	enum Axis
	{
		X,
		Y,
		Z
	};

	// 衝突結果に関する情報をまとめている
	struct CollisionInfo
	{
		// 衝突点
		Vector3				mPoint;
		// 衝突時の座標
		Vector3				mNormal;
		float				mT;
		// 衝突クラス
		class Collider*		mCollider;
		// コンポーネントの所有Actor
		class ActorObject*	mActor;
	};

	struct ContactPoint
	{
		Vector3 normal;        // 接触法線
		float penetration;     // めり込み深さ
	};

private:
	class BaseScene*									mGame;

	vector<class Collider*>								mCollider;

	vector<class Collider*>								mColliderXAxis;

	vector<class Collider*>								mColliderYAxis;

	vector<class Collider*>								mColliderZAxis;

	std::set<std::pair<Collider*, Collider*>>			mHitColliderXAxis;

	std::set<std::pair<Collider*, Collider*>>			mHitColliderYAxis;

	std::set<std::pair<Collider*, Collider*>>			mHitColliderZAxis;


	std::set<std::pair<ActorObject*, ActorObject*>>		mPrevHitPairs;

	std::set<std::pair<ActorObject*, ActorObject*>>		mCurrentHitPairs;

public:

														PhysWorld(class BaseScene* game);

	// 線分をボックスに対して判定します。
	// ボックスに衝突する場合は真を返します。
	bool												RayCast(const LineSegment& l, CollisionInfo& outColl);
	vector<CollisionInfo>								RayCastAll(const LineSegment& l);

	//素朴なpairwise衝突判定
	void												TestPairwise(std::function<void(class ActorObject*, class ActorObject*)> f);

	//XYZのSweeppruneを使用した衝突判定
	void												SweepAndPruneXYZ();

	void												FixCollisions(class Collider* dynamicCollider, class Collider* staticCollider);
	//AABBでの押し出しに使用する関数
	bool												GetContactInfo(const AABB& a, const AABB& b, Vector3& outNormal, float& outDepth);

	void												CollectContactPoints(const AABB& a, const AABB& b, std::vector<ContactPoint>& outContacts, float contactOffset);
	Vector3												CalculatePushVector(const std::vector<ContactPoint>& contacts, float contactOffset);
	//OBBでの押し出しに使用する関数
	/*
	void												CollectContactPoints(const OBB& a, const OBB& b, std::vector<ContactPoint>& outContacts, float contactOffset);
	
	bool												GetContactInfo_OBB(const OBB& a, const OBB& b, Vector3& outNormal, float& outDepth);

	bool												OnCollision_OBB(const OBB& a, const OBB& b);

	bool												TestAxis(const Vector3& axis, const OBB& a, const OBB& b);

	void												ProjectOBB(const OBB& obb, const Vector3& axis, float& outMin, float& outMax);
	*/
	// 世界からボックスコンポーネントを追加/削除する
	void												AddCollider(class Collider* box);
	void												RemoveCollider(class Collider* box);
};