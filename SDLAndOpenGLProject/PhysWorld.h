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
		// ボックス衝突クラス
		class BoxCollider* mBox;
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

	void SortColliderXAxis();
	void SortColliderYAxis();
	void SortColliderZAxis();

	//XYZのSweeppruneを使用した衝突判定
	void SweepAndPruneXYZ();

	// 世界からボックスコンポーネントを追加/削除する
	void AddBox(class BoxCollider* box);
	void RemoveBox(class BoxCollider* box);
private:
	class BaseScene* mGame;
	//元のBox
	std::vector<class BoxCollider*> mBoxes;
	
	std::vector<class BoxCollider*> mBoxesXAxis;

	std::vector<class BoxCollider*> mBoxesYAxis;
	
	std::vector<class BoxCollider*> mBoxesZAxis;

	std::set<std::pair<BoxCollider*, BoxCollider*>> mHitBoxesXAxis;

	std::set<std::pair<BoxCollider*, BoxCollider*>> mHitBoxesYAxis;

	std::set<std::pair<BoxCollider*, BoxCollider*>> mHitBoxesZAxis;

	std::set<std::pair<ActorObject*, ActorObject*>> mPrevHitPairs;

	std::set<std::pair<ActorObject*, ActorObject*>> mCurrentHitPairs;

	//std::vector<class Collider*> mCollider;
};