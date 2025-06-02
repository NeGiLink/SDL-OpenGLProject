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
			if (t >= 0.0f && t < closestT)
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

vector<PhysWorld::CollisionInfo> PhysWorld::RayCastAll(const LineSegment& l)
{
	std::vector<CollisionInfo> results;

	for (auto collider : mCollider)
	{
		float t = 0.0f;
		Vector3 norm;
		if (OnCollision(l, collider->GetWorldBox(), t, norm))
		{
			if (t >= 0.0f && t <= 1.0f)
			{
				CollisionInfo info;
				info.mT = t;
				info.mPoint = l.PointOnSegment(t);
				info.mNormal = norm;
				info.mCollider = collider;
				info.mActor = collider->GetOwner();
				results.push_back(info);
			}
		}
	}

	// t値（手前順）でソートする
	std::sort(results.begin(), results.end(),
		[](const CollisionInfo& a, const CollisionInfo& b)
		{
			return a.mT < b.mT;
		});

	return results;
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
	ActorObject* dynamicActor = dynamicCollider->GetOwner();

	int solverIterationCount = 1;
	if (dynamicActor->GetRigidbody())
	{
		solverIterationCount = dynamicActor->GetRigidbody()->GetSolverIterationCount();
	}

	const float pushLerpFactor = 0.2f;
	bool resolved = false;
	Axis resolvedAxis = Axis::X;

	for (int i = 0; i < solverIterationCount; ++i)
	{
		Vector3 pos = dynamicActor->GetPosition();

		// === 接触点収集 ===
		std::vector<ContactPoint> contactPoints;
		CollectContactPoints(dynamicCollider->GetWorldBox(), staticCollider->GetWorldBox(), contactPoints, contactOffset);

		if (contactPoints.empty())
			break;

		// === 複合押し出しベクトル計算 ===
		Vector3 totalPush = Vector3::Zero;
		float totalWeight = 0.0f;

		for (const auto& cp : contactPoints)
		{
			totalPush += cp.normal * (cp.penetration + contactOffset);
			totalWeight += cp.penetration;
		}

		Vector3 push = (totalWeight > 0.0f) ? totalPush / static_cast<float>(contactPoints.size()) : Vector3::Zero;

		// === 位置補正（Lerp）===
		Vector3 target = pos + push;
		pos = Vector3::Lerp(pos, target, pushLerpFactor);

		dynamicActor->SetLocalPosition(pos);
		dynamicCollider->OnUpdateWorldTransform();

		// === 主軸推定（速度補正用）===
		if (push.LengthSq() > 0.0f)
		{
			if (std::abs(push.x) > std::abs(push.y) && std::abs(push.x) > std::abs(push.z))
				resolvedAxis = X;
			else if (std::abs(push.y) > std::abs(push.x) && std::abs(push.y) > std::abs(push.z))
				resolvedAxis = Y;
			else
				resolvedAxis = Z;
		}

		resolved = true;

		// 解消されたら早期終了
		if (!OnCollision(dynamicCollider->GetWorldBox(), staticCollider->GetWorldBox()))
			break;
	}

	// === 速度補正 ===
	if (resolved && dynamicActor->GetRigidbody())
	{
		Vector3 velocity = dynamicActor->GetRigidbody()->GetVelocity();
		velocity = dynamicActor->GetRigidbody()->ResolveCollision(velocity, resolvedAxis);
		dynamicActor->GetRigidbody()->SetVelocity(velocity);
	}
}

bool PhysWorld::GetContactInfo(const AABB& a, const AABB& b, Vector3& outNormal, float& outDepth)
{
	float dx1 = b.mMax.x - a.mMin.x;
	float dx2 = b.mMin.x - a.mMax.x;
	float dy1 = b.mMax.y - a.mMin.y;
	float dy2 = b.mMin.y - a.mMax.y;
	float dz1 = b.mMax.z - a.mMin.z;
	float dz2 = b.mMin.z - a.mMax.z;

	float dx = (Math::Abs(dx1) < Math::Abs(dx2)) ? dx1 : dx2;
	float dy = (Math::Abs(dy1) < Math::Abs(dy2)) ? dy1 : dy2;
	float dz = (Math::Abs(dz1) < Math::Abs(dz2)) ? dz1 : dz2;

	// 最小の交差軸を選ぶ
	if (Math::Abs(dx) < Math::Abs(dy) && Math::Abs(dx) < Math::Abs(dz))
	{
		outNormal = Vector3(Math::Sign(dx), 0, 0);
		outDepth = Math::Abs(dx);
	}
	else if (Math::Abs(dy) < Math::Abs(dx) && Math::Abs(dy) < Math::Abs(dz))
	{
		outNormal = Vector3(0, Math::Sign(dy), 0);
		outDepth = Math::Abs(dy);
	}
	else
	{
		outNormal = Vector3(0, 0, Math::Sign(dz));
		outDepth = Math::Abs(dz);
	}

	return true;
}

void PhysWorld::CollectContactPoints(const AABB& a, const AABB& b, std::vector<ContactPoint>& outContacts, float contactOffset)
{
	float dx1 = b.mMax.x - a.mMin.x;
	float dx2 = b.mMin.x - a.mMax.x;
	float dy1 = b.mMax.y - a.mMin.y;
	float dy2 = b.mMin.y - a.mMax.y;
	float dz1 = b.mMax.z - a.mMin.z;
	float dz2 = b.mMin.z - a.mMax.z;

	float dx = (std::abs(dx1) < std::abs(dx2)) ? dx1 : dx2;
	float dy = (std::abs(dy1) < std::abs(dy2)) ? dy1 : dy2;
	float dz = (std::abs(dz1) < std::abs(dz2)) ? dz1 : dz2;

	float absDx = std::abs(dx);
	float absDy = std::abs(dy);
	float absDz = std::abs(dz);

	// 最小の交差量を取得（基準）
	float minDepth = std::min({ absDx, absDy, absDz });

	// 基準に近い（または同じ）方向だけを接触点とみなす
	const float tolerance = 0.001f; // 小さな誤差を許容

	if (absDx - minDepth <= tolerance)
	{
		outContacts.push_back({ Vector3(Math::Sign(dx), 0, 0), absDx });
	}
	if (absDy - minDepth <= tolerance)
	{
		outContacts.push_back({ Vector3(0, Math::Sign(dy), 0), absDy });
	}
	if (absDz - minDepth <= tolerance)
	{
		outContacts.push_back({ Vector3(0, 0, Math::Sign(dz)), absDz });
	}
}

Vector3 PhysWorld::CalculatePushVector(const std::vector<ContactPoint>& contacts, float contactOffset)
{
	Vector3 totalPush = Vector3::Zero;
	float totalWeight = 0.0f;

	for (const auto& cp : contacts)
	{
		totalPush += cp.normal * (cp.penetration + contactOffset);
		totalWeight += cp.penetration;
	}

	if (totalWeight > 0.0f)
		return totalPush / static_cast<float>(contacts.size());
	else
		return Vector3::Zero;
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
