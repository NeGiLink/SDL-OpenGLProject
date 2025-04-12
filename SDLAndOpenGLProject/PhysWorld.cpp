#include "PhysWorld.h"
#include <algorithm>
#include "BoxComponent.h"
#include <SDL3/SDL.h>

PhysWorld::PhysWorld(BaseScene* game)
	:mGame(game)
{
}

bool PhysWorld::SegmentCast(const LineSegment& l, CollisionInfo& outColl)
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
		if (Intersect(l, box->GetWorldBox(), t, norm))
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
			BoxComponent* a = mBoxes[i];
			BoxComponent* b = mBoxes[j];
			if (Intersect(a->GetWorldBox(), b->GetWorldBox()))
			{
				// 交差点を処理するために提供された関数を呼び出す
				f(a->GetOwner(), b->GetOwner());
			}
		}
	}
}

void PhysWorld::TestSweepAndPrune(std::function<void(ActorObject*, ActorObject*)> f)
{
	// Sort by min.x
	std::sort(mBoxes.begin(), mBoxes.end(),
		[](BoxComponent* a, BoxComponent* b) {
			return a->GetWorldBox().mMin.x <
				b->GetWorldBox().mMin.x;
		});

	for (size_t i = 0; i < mBoxes.size(); i++)
	{
		// 現在のボックスに対してmax.xを取得する
		BoxComponent* a = mBoxes[i];
		float max = a->GetWorldBox().mMax.x;
		for (size_t j = i + 1; j < mBoxes.size(); j++)
		{
			BoxComponent* b = mBoxes[j];
			// AABB[j]の最小値がAABB[i]の最大値を超えている場合、
			// AABB[i]との交差は他に存在しないためbreak
			if (b->GetWorldBox().mMin.x > max)
			{
				break;
			}
			else if (Intersect(a->GetWorldBox(), b->GetWorldBox()))
			{
				f(a->GetOwner(), b->GetOwner());
			}
		}
	}
}

void PhysWorld::AddBox(BoxComponent* box)
{
	mBoxes.emplace_back(box);
}

void PhysWorld::RemoveBox(BoxComponent* box)
{
	auto iter = std::find(mBoxes.begin(), mBoxes.end(), box);
	if (iter != mBoxes.end())
	{
		// ベクトルの末尾にスワップし、
		// ポップオフします（コピーの消去を避けるため）
		std::iter_swap(iter, mBoxes.end() - 1);
		mBoxes.pop_back();
	}
}