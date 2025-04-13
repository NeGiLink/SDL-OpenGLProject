#include "PhysWorld.h"
#include <algorithm>
#include "BoxCollider.h"
#include "Collider.h"
#include "Actor.h"
#include <SDL3/SDL.h>

PhysWorld::PhysWorld(BaseScene* game)
	:mGame(game)
{
}

bool PhysWorld::RayCast(const LineSegment& l, CollisionInfo& outColl)
{
	bool collided = false;
	// closestTを無限大に初期化して、
	// 最初の交差点が常にclosestTを更新するようにします。
	float closestT = Math::Infinity;
	Vector3 norm;
	// すべてのボックスに対する判定
	for (auto box : mBoxes)
	{
		float t;
		// その線分はボックスと交差しているか判定
		if (OnCollision(l, box->GetWorldBox(), t, norm))
		{
			// これは以前の交差点より近いか
			if (t < closestT)
			{
				closestT = t;
				outColl.mPoint = l.PointOnSegment(t);
				outColl.mNormal = norm;
				outColl.mBox = box;
				outColl.mActor = box->GetOwner();
				collided = true;
			}
		}
	}
	return collided;
}

void PhysWorld::TestPairwise(std::function<void(ActorObject*, ActorObject*)> f)
{
	// 単純な実装 O(n^2)
	for (size_t i = 0; i < mBoxes.size(); i++)
	{
		// 自分自身や以前のi値に対してテストする必要はなし
		for (size_t j = i + 1; j < mBoxes.size(); j++)
		{
			BoxCollider* a = mBoxes[i];
			BoxCollider* b = mBoxes[j];
			if (OnCollision(a->GetWorldBox(), b->GetWorldBox()))
			{
				// 交差点を処理するために提供された関数を呼び出す
				f(a->GetOwner(), b->GetOwner());
			}
		}
	}
}

//X軸Ver
void PhysWorld::SortColliderXAxis()
{

	for (size_t i = 0; i < mBoxes.size(); i++)
	{
		// 現在のボックスに対してmax.xを取得する
		BoxCollider* a = mBoxes[i];
		float max = a->GetWorldBox().mMax.x;
		for (size_t j = i + 1; j < mBoxes.size(); j++)
		{
			BoxCollider* b = mBoxes[j];
			// AABB[j]の最小値がAABB[i]の最大値を超えている場合、
			// AABB[i]との交差は他に存在しないためbreak
			if (b->GetWorldBox().mMin.x > max)
			{
				break;
			}
			else if (OnCollision(a->GetWorldBox(), b->GetWorldBox()))
			{
				mHitBoxesXAxis.emplace(a, b);
			}
		}
	}
}
//Y軸Ver
void PhysWorld::SortColliderYAxis()
{

	for (size_t i = 0; i < mBoxes.size(); i++)
	{
		// 現在のボックスに対してmax.xを取得する
		BoxCollider* a = mBoxes[i];
		float max = a->GetWorldBox().mMax.y;
		for (size_t j = i + 1; j < mBoxes.size(); j++)
		{
			BoxCollider* b = mBoxes[j];
			// AABB[j]の最小値がAABB[i]の最大値を超えている場合、
			// AABB[i]との交差は他に存在しないためbreak
			if (b->GetWorldBox().mMin.y > max)
			{
				break;
			}
			else if (OnCollision(a->GetWorldBox(), b->GetWorldBox()))
			{
				mHitBoxesYAxis.emplace(a, b);
			}
		}
	}
}
//Z軸Ver
void PhysWorld::SortColliderZAxis()
{

	for (size_t i = 0; i < mBoxes.size(); i++)
	{
		// 現在のボックスに対してmax.xを取得する
		BoxCollider* a = mBoxes[i];
		float max = a->GetWorldBox().mMax.z;
		for (size_t j = i + 1; j < mBoxes.size(); j++)
		{
			BoxCollider* b = mBoxes[j];
			// AABB[j]の最小値がAABB[i]の最大値を超えている場合、
			// AABB[i]との交差は他に存在しないためbreak
			if (b->GetWorldBox().mMin.z > max)
			{
				break;
			}
			else if (OnCollision(a->GetWorldBox(), b->GetWorldBox()))
			{
				mHitBoxesZAxis.emplace(a, b);
			}
		}
	}
}

void PhysWorld::SweepAndPruneXYZ()
{
	// まずX軸でソート
	std::sort(mBoxesXAxis.begin(), mBoxesXAxis.end(),
		[](BoxCollider* a, BoxCollider* b) {
			return a->GetWorldBox().mMin.x < b->GetWorldBox().mMin.x;
		});

	std::sort(mBoxesYAxis.begin(), mBoxesYAxis.end(),
		[](BoxCollider* a, BoxCollider* b) {
			return a->GetWorldBox().mMin.y < b->GetWorldBox().mMin.y;
		});

	std::sort(mBoxesZAxis.begin(), mBoxesZAxis.end(),
		[](BoxCollider* a, BoxCollider* b) {
			return a->GetWorldBox().mMin.y < b->GetWorldBox().mMin.y;
		});

	// 各軸の判定
	mHitBoxesXAxis.clear();
	mHitBoxesYAxis.clear();
	mHitBoxesZAxis.clear();

	SortColliderXAxis();
	SortColliderYAxis();
	SortColliderZAxis();

	mCurrentHitPairs.clear();

	// 共通ペアの検出
	for (const auto& pair : mHitBoxesXAxis)
	{
		if (mHitBoxesYAxis.count(pair) && mHitBoxesZAxis.count(pair))
		{
			auto actorA = pair.first->GetOwner();
			auto actorB = pair.second->GetOwner();

			std::pair<ActorObject*, ActorObject*> sortedPair = actorA < actorB ?
				std::make_pair(actorA, actorB) : std::make_pair(actorB, actorA);

			mCurrentHitPairs.emplace(sortedPair);

			if (mPrevHitPairs.count(sortedPair))
			{
				// Stay
				actorA->OnCollisionStay(actorB);
				actorB->OnCollisionStay(actorA);
			}
			else
			{
				// Enter
				actorA->OnCollisionEnter(actorB);
				actorB->OnCollisionEnter(actorA);
			}
		}
	}

	// Exitチェック
	for (const auto& pair : mPrevHitPairs)
	{
		if (mCurrentHitPairs.count(pair) == 0)
		{
			auto actorA = pair.first;
			auto actorB = pair.second;
			actorA->OnCollisionExit(actorB);
			actorB->OnCollisionExit(actorA);
		}
	}

	// 状態更新
	mPrevHitPairs = mCurrentHitPairs;
}

void PhysWorld::AddBox(BoxCollider* box)
{
	mBoxes.emplace_back(box);
	mBoxesXAxis.emplace_back(box);
	mBoxesYAxis.emplace_back(box);
	mBoxesZAxis.emplace_back(box);
}

void PhysWorld::RemoveBox(BoxCollider* box)
{
	auto iter = std::find(mBoxes.begin(), mBoxes.end(), box);
	if (iter != mBoxes.end())
	{
		// ベクトルの末尾にスワップし、
		// ポップオフします（コピーの消去を避けるため）
		std::iter_swap(iter, mBoxes.end() - 1);
		mBoxes.pop_back();
	}

	iter = std::find(mBoxesXAxis.begin(), mBoxesXAxis.end(), box);
	if (iter != mBoxesXAxis.end())
	{
		// ベクトルの末尾にスワップし、
		// ポップオフします（コピーの消去を避けるため）
		std::iter_swap(iter, mBoxesXAxis.end() - 1);
		mBoxesXAxis.pop_back();
	}

	iter = std::find(mBoxesYAxis.begin(), mBoxesYAxis.end(), box);
	if (iter != mBoxesYAxis.end())
	{
		// ベクトルの末尾にスワップし、
		// ポップオフします（コピーの消去を避けるため）
		std::iter_swap(iter, mBoxesYAxis.end() - 1);
		mBoxesYAxis.pop_back();
	}

	iter = std::find(mBoxesZAxis.begin(), mBoxesZAxis.end(), box);
	if (iter != mBoxesZAxis.end())
	{
		// ベクトルの末尾にスワップし、
		// ポップオフします（コピーの消去を避けるため）
		std::iter_swap(iter, mBoxesZAxis.end() - 1);
		mBoxesZAxis.pop_back();
	}


}