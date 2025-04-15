#include "PhysWorld.h"
#include <algorithm>
#include "BoxCollider.h"
#include "SphereCollider.h"
#include "CapsuleCollider.h"
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
	for (auto collider : mCollider)
	{
		float t;
		// その線分はボックスと交差しているか判定
		if (OnCollision(l, collider->GetWorldBox(), t, norm))
		{
			// これは以前の交差点より近いか
			if (t < closestT)
			{
				closestT = t;
				outColl.mPoint = l.PointOnSegment(t);
				outColl.mNormal = norm;
				outColl.mCollider = collider;
				outColl.mActor = collider->GetOwner();
				collided = true;
			}
		}
	}
	return collided;
}

void PhysWorld::TestPairwise(std::function<void(ActorObject*, ActorObject*)> f)
{
	// 単純な実装 O(n^2)
	for (size_t i = 0; i < mCollider.size(); i++)
	{
		// 自分自身や以前のi値に対してテストする必要はなし
		for (size_t j = i + 1; j < mCollider.size(); j++)
		{
			Collider* a = mCollider[i];
			Collider* b = mCollider[j];
			if (OnCollision(a->GetWorldBox(), b->GetWorldBox()))
			{
				// 交差点を処理するために提供された関数を呼び出す
				f(a->GetOwner(), b->GetOwner());
			}
		}
	}
}

//X軸Ver
void PhysWorld::DecideColliderXAxis()
{

	for (size_t i = 0; i < mCollider.size(); i++)
	{
		// 現在のボックスに対してmax.xを取得する
		Collider* a = mCollider[i];
		float max = a->GetWorldBox().mMax.x;
		for (size_t j = i + 1; j < mCollider.size(); j++)
		{
			Collider* b = mCollider[j];
			// AABB[j]の最小値がAABB[i]の最大値を超えている場合、
			// AABB[i]との交差は他に存在しないためbreak
			if (b->GetWorldBox().mMin.x > max)
			{
				break;
			}
			else if (OnAllCollision(a, b))
			{
				mHitColliderXAxis.emplace(a, b);
			}
		}
	}
}
//Y軸Ver
void PhysWorld::DecideColliderYAxis()
{

	for (size_t i = 0; i < mCollider.size(); i++)
	{
		// 現在のボックスに対してmax.xを取得する
		Collider* a = mCollider[i];
		float max = a->GetWorldBox().mMax.y;
		for (size_t j = i + 1; j < mCollider.size(); j++)
		{
			Collider* b = mCollider[j];
			// AABB[j]の最小値がAABB[i]の最大値を超えている場合、
			// AABB[i]との交差は他に存在しないためbreak
			if (b->GetWorldBox().mMin.y > max)
			{
				break;
			}
			else if (OnAllCollision(a, b))
			{
				mHitColliderYAxis.emplace(a, b);
			}
		}
	}
}
//Z軸Ver
void PhysWorld::DecideColliderZAxis()
{

	for (size_t i = 0; i < mCollider.size(); i++)
	{
		// 現在のボックスに対してmax.xを取得する
		Collider* a = mCollider[i];
		float max = a->GetWorldBox().mMax.z;
		for (size_t j = i + 1; j < mCollider.size(); j++)
		{
			Collider* b = mCollider[j];
			// AABB[j]の最小値がAABB[i]の最大値を超えている場合、
			// AABB[i]との交差は他に存在しないためbreak
			if (b->GetWorldBox().mMin.z > max)
			{
				break;
			}
			else if (OnAllCollision(a, b))
			{
				mHitColliderZAxis.emplace(a, b);
			}
		}
	}
}

bool PhysWorld::OnAllCollision(Collider* a, Collider* b)
{
	//Box Box
	if (a->GetType() == Collider::BoxType && b->GetType() == Collider::BoxType)
	{
		return OnCollision(a->GetWorldBox(), b->GetWorldBox());
	}
	//Sphere Sphere
	if (a->GetType() == Collider::SphereType && b->GetType() == Collider::SphereType)
	{
		return OnCollision(a->GetWorldSphere(), b->GetWorldSphere());
	}
	//Capsule Capsule
	if (a->GetType() == Collider::CapsuleType && b->GetType() == Collider::CapsuleType)
	{
		return OnCollision(a->GetWorldCapsule(), b->GetWorldCapsule());
	}
	//Box Sphere
	if (a->GetType() == Collider::BoxType && b->GetType() == Collider::SphereType) 
	{
		return OnCollision(a->GetWorldBox(), b->GetWorldSphere());
	}
	//Sphere Box
	if (a->GetType() == Collider::SphereType && b->GetType() == Collider::BoxType)
	{
		return OnCollision(a->GetWorldSphere(), b->GetWorldBox());
	}
	//Box Capsule
	if (a->GetType() == Collider::BoxType && b->GetType() == Collider::CapsuleType) 
	{
		return OnCollision(a->GetWorldBox(), b->GetWorldCapsule());
	}
	//Capsule Box
	if (a->GetType() == Collider::CapsuleType && b->GetType() == Collider::BoxType)
	{
		return OnCollision(a->GetWorldCapsule(), b->GetWorldBox());
	}
	//Sphere Capsule
	if (a->GetType() == Collider::SphereType && b->GetType() == Collider::CapsuleType)
	{
		return OnCollision(a->GetWorldSphere(), b->GetWorldCapsule());
	}
	//Capsule Sphere
	if (a->GetType() == Collider::CapsuleType && b->GetType() == Collider::SphereType)
	{
		return OnCollision(a->GetWorldCapsule(), b->GetWorldSphere());
	}
}

void PhysWorld::SweepAndPruneXYZ()
{
	// まずX軸でソート
	std::sort(mColliderXAxis.begin(), mColliderXAxis.end(),
		[](Collider* a, Collider* b) {
			return a->GetWorldBox().mMin.x < b->GetWorldBox().mMin.x;
		});

	std::sort(mColliderYAxis.begin(), mColliderYAxis.end(),
		[](Collider* a, Collider* b) {
			return a->GetWorldBox().mMin.y < b->GetWorldBox().mMin.y;
		});

	std::sort(mColliderZAxis.begin(), mColliderZAxis.end(),
		[](Collider* a, Collider* b) {
			return a->GetWorldBox().mMin.z < b->GetWorldBox().mMin.z;
		});

	mHitColliderXAxis.clear();
	mHitColliderYAxis.clear();
	mHitColliderZAxis.clear();

	// 各軸の判定
	DecideColliderXAxis();
	DecideColliderYAxis();
	DecideColliderZAxis();

	mCurrentHitPairs.clear();

	// 共通ペアの検出
	for (const auto& pair : mHitColliderXAxis)
	{
		if (mHitColliderYAxis.count(pair) && mHitColliderZAxis.count(pair))
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
				SDL_Log("actorA %d", (int)pair.first->GetType());
				SDL_Log("actorB %d", (int)pair.second->GetType());
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

void PhysWorld::AddCollider(Collider* box)
{
	mCollider.push_back(box);
	mColliderXAxis.emplace_back(box);
	mColliderYAxis.emplace_back(box);
	mColliderZAxis.emplace_back(box);
}

void PhysWorld::RemoveCollider(Collider* box)
{
	auto iter = std::find(mCollider.begin(), mCollider.end(), box);
	if (iter != mCollider.end())
	{
		// ベクトルの末尾にスワップし、
		// ポップオフします（コピーの消去を避けるため）
		std::iter_swap(iter, mCollider.end() - 1);
		mCollider.pop_back();
	}

	iter = std::find(mColliderXAxis.begin(), mColliderXAxis.end(), box);
	if (iter != mColliderXAxis.end())
	{
		// ベクトルの末尾にスワップし、
		// ポップオフします（コピーの消去を避けるため）
		std::iter_swap(iter, mColliderXAxis.end() - 1);
		mColliderXAxis.pop_back();
	}

	iter = std::find(mColliderYAxis.begin(), mColliderYAxis.end(), box);
	if (iter != mColliderYAxis.end())
	{
		// ベクトルの末尾にスワップし、
		// ポップオフします（コピーの消去を避けるため）
		std::iter_swap(iter, mColliderYAxis.end() - 1);
		mColliderYAxis.pop_back();
	}

	iter = std::find(mColliderZAxis.begin(), mColliderZAxis.end(), box);
	if (iter != mColliderZAxis.end())
	{
		// ベクトルの末尾にスワップし、
		// ポップオフします（コピーの消去を避けるため）
		std::iter_swap(iter, mColliderZAxis.end() - 1);
		mColliderZAxis.pop_back();
	}
}
