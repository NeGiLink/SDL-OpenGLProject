#pragma once
#include <vector>
#include <functional>
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
		class BoxComponent* mBox;
		// コンポーネントの所有Actor
		class ActorObject*	mActor;
	};

	// 線分をボックスに対して判定します。
	// ボックスに衝突する場合は真を返します。
	bool SegmentCast(const LineSegment& l, CollisionInfo& outColl);

	//素朴なpairwise衝突判定
	void TestPairwise(std::function<void(class ActorObject*, class ActorObject*)> f);

	//sweepprune使用した衝突判定
	void TestSweepAndPrune(std::function<void(class ActorObject*, class ActorObject*)> f);

	// 世界からボックスコンポーネントを追加/削除する
	void AddBox(class BoxComponent* box);
	void RemoveBox(class BoxComponent* box);
private:
	class BaseScene* mGame;
	std::vector<class BoxComponent*> mBoxes;
};