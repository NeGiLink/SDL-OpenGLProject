#include "PhysWorld.h"
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
	Vector3 norm = Vector3::Zero;
	// すべてのボックスに対する判定
	for (auto collider : mCollider)
	{
		float t = 0;
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

void PhysWorld::SweepAndPruneXYZ()
{
	// まずX軸でソート
	std::sort(mColliderXAxis.begin(), mColliderXAxis.end(),
		[](Collider* a, Collider* b) {
			return a->GetWorldBox().mMin.x < b->GetWorldBox().mMin.x;
		});

	mCurrentHitPairs.clear();

	// X軸スイープ開始
	for (size_t i = 0; i < mColliderXAxis.size(); ++i)
	{
		Collider* colliderA = mColliderXAxis[i];
		const AABB& aabbA = colliderA->GetWorldBox();

		for (size_t j = i + 1; j < mColliderXAxis.size(); ++j)
		{
			Collider* colliderB = mColliderXAxis[j];
			const AABB& aabbB = colliderB->GetWorldBox();

			const float contactOffset = 0.001f;

			const float contactOffsetA = colliderA->GetContactOffset();
			const float contactOffsetB = colliderB->GetContactOffset();

			// X軸の最大と最小が交差してなかったらbreak（高速化）
			// ※ contactOffset を加味して比較
			if (aabbB.mMin.x - contactOffsetB > aabbA.mMax.x + contactOffsetA)
			{
				break;
			}

			// Y軸とZ軸の交差判定にも contactOffset を考慮
			if (aabbA.mMax.y + contactOffsetA < aabbB.mMin.y - contactOffsetB ||
				aabbA.mMin.y - contactOffsetA > aabbB.mMax.y + contactOffsetB)
			{
				continue;
			}

			if (aabbA.mMax.z + contactOffsetA < aabbB.mMin.z - contactOffsetB ||
				aabbA.mMin.z - contactOffsetA > aabbB.mMax.z + contactOffsetB)
			{
				continue;
			}

			// ここまで来たらAとBは当たっている
			auto actorA = colliderA->GetOwner();
			auto actorB = colliderB->GetOwner();

			std::pair<ActorObject*, ActorObject*> sortedPair = actorA < actorB ?
				std::make_pair(actorA, actorB) : std::make_pair(actorB, actorA);

			mCurrentHitPairs.emplace(sortedPair);

			// Enter or Stay判定
			if (mPrevHitPairs.count(sortedPair))
			{
				actorA->OnCollisionStay(actorB);
				actorB->OnCollisionStay(actorA);
				//当たり続けている時も判定
				if (!colliderA->IsStaticObject() && colliderB->IsStaticObject())
				{
					FixCollisions(colliderA, colliderB);
				}
				else 
				if (colliderA->IsStaticObject() && !colliderB->IsStaticObject())
				{
					FixCollisions(colliderB, colliderA);
				}
			}
			else
			{
				actorA->OnCollisionEnter(actorB);
				actorB->OnCollisionEnter(actorA);

				//当たり初めに判定
				if (!colliderA->IsStaticObject() && colliderB->IsStaticObject())
				{
					FixCollisions(colliderA, colliderB);
				}
				else 
				if (colliderA->IsStaticObject() && !colliderB->IsStaticObject())
				{
					FixCollisions(colliderB, colliderA);
				}
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

void PhysWorld::FixCollisions(class Collider* dynamicCollider, class Collider* staticCollider)
{
	const float contactOffset = dynamicCollider->GetContactOffset();

	dynamicCollider->GetOwner()->ComputeWorldTransform(NULL);

	ActorObject* dynamicActor = dynamicCollider->GetOwner();
	Vector3 pos = dynamicActor->GetLocalPosition();
	
	// 平面の違いを計算
	float dx1 = staticCollider->GetWorldBox().mMax.x - dynamicCollider->GetWorldBox().mMin.x;
	float dx2 = staticCollider->GetWorldBox().mMin.x - dynamicCollider->GetWorldBox().mMax.x;
	float dy1 = staticCollider->GetWorldBox().mMax.y - dynamicCollider->GetWorldBox().mMin.y;
	float dy2 = staticCollider->GetWorldBox().mMin.y - dynamicCollider->GetWorldBox().mMax.y;
	float dz1 = staticCollider->GetWorldBox().mMax.z - dynamicCollider->GetWorldBox().mMin.z;
	float dz2 = staticCollider->GetWorldBox().mMin.z - dynamicCollider->GetWorldBox().mMax.z;

	// dxをdx1またはdx2のうち、絶対値が低い方に設定。
	float dx = Math::Abs(dx1) < Math::Abs(dx2) ?
		dx1 : dx2;
	// dyについても同様
	float dy = Math::Abs(dy1) < Math::Abs(dy2) ?
		dy1 : dy2;
	// dzについても同様
	float dz = Math::Abs(dz1) < Math::Abs(dz2) ?
		dz1 : dz2;

	Axis collisionAxis;
	// 最も近い方に応じてx/y位置を調整
	if (Math::Abs(dx) < Math::Abs(dy) && Math::Abs(dx) < Math::Abs(dz))
	{
		pos.x += dx + Math::Sign(dx) * contactOffset;
		collisionAxis = X;
	}
	else if (Math::Abs(dy) < Math::Abs(dx) && Math::Abs(dy) < Math::Abs(dz))
	{
		pos.y += dy + Math::Sign(dy) * contactOffset;
		collisionAxis = Y;
	}
	else
	{
		pos.z += dz + Math::Sign(dz) * contactOffset;
		collisionAxis = Z;
	}

	// ポジションを設定し、ボックスコンポーネントを更新する必要があります。
	if (dynamicActor->GetRigidbody())
	{
		Vector3 velocity = dynamicActor->GetRigidbody()->GetVelocity();

		if (collisionAxis == X)
		{
			velocity.x = 0.0f;
		}
		else if (collisionAxis == Y)
		{
			velocity.y = 0.0f;
		}
		else if (collisionAxis == Z)
		{
			velocity.z = 0.0f;
		}

		dynamicActor->GetRigidbody()->SetVelocity(velocity);
	}
	//平行移動を更新
	dynamicActor->SetLocalPosition(pos);
	//コライダーの座標更新
	dynamicCollider->OnUpdateWorldTransform();
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
