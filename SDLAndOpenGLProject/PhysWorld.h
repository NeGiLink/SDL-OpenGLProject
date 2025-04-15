#pragma once
#include "STD.h"
#include "Math.h"
#include "Collision.h"

class PhysWorld
{
public:
	PhysWorld(class BaseScene* game);

	// 衝突結果に関する情報をまとめている
	struct CollisionInfo
	{
		// 衝突点
		Vector3				mPoint;
		// 衝突時の座標
		Vector3				mNormal;
		// 衝突クラス
		class Collider*		mCollider;
		// コンポーネントの所有Actor
		class ActorObject*	mActor;
	};

	// 線分をボックスに対して判定します。
	// ボックスに衝突する場合は真を返します。
	bool RayCast(const LineSegment& l, CollisionInfo& outColl);

	//素朴なpairwise衝突判定
	void TestPairwise(std::function<void(class ActorObject*, class ActorObject*)> f);

	//sweepprune使用した衝突判定
	//void TestSweepAndPrune(std::function<void(class ActorObject*, class ActorObject*)> f);

	void DecideColliderXAxis();
	void DecideColliderYAxis();
	void DecideColliderZAxis();
	//基底Colliderで二つのColliderを比較する関数
	bool OnAllCollision(class Collider* a,class Collider* b);

	//XYZのSweeppruneを使用した衝突判定
	void SweepAndPruneXYZ();

	// 世界からボックスコンポーネントを追加/削除する
	void AddCollider(class Collider* box);
	void RemoveCollider(class Collider* box);
private:
	class BaseScene* mGame;

	std::vector<class Collider*> mCollider;

	std::vector<class Collider*> mColliderXAxis;

	std::vector<class Collider*> mColliderYAxis;

	std::vector<class Collider*> mColliderZAxis;

	std::set<std::pair<Collider*, Collider*>> mHitColliderXAxis;

	std::set<std::pair<Collider*, Collider*>> mHitColliderYAxis;

	std::set<std::pair<Collider*, Collider*>> mHitColliderZAxis;


	std::set<std::pair<ActorObject*, ActorObject*>> mPrevHitPairs;

	std::set<std::pair<ActorObject*, ActorObject*>> mCurrentHitPairs;
};