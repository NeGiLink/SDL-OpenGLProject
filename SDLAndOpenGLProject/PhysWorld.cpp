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
	// closestT�𖳌���ɏ��������āA
	// �ŏ��̌����_�����closestT���X�V����悤�ɂ��܂��B
	float closestT = Math::Infinity;
	Vector3 norm;
	// ���ׂẴ{�b�N�X�ɑ΂��锻��
	for (auto collider : mCollider)
	{
		float t;
		// ���̐����̓{�b�N�X�ƌ������Ă��邩����
		if (OnCollision(l, collider->GetWorldBox(), t, norm))
		{
			// ����͈ȑO�̌����_���߂���
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
	// �P���Ȏ��� O(n^2)
	for (size_t i = 0; i < mCollider.size(); i++)
	{
		// �������g��ȑO��i�l�ɑ΂��ăe�X�g����K�v�͂Ȃ�
		for (size_t j = i + 1; j < mCollider.size(); j++)
		{
			Collider* a = mCollider[i];
			Collider* b = mCollider[j];
			if (OnCollision(a->GetWorldBox(), b->GetWorldBox()))
			{
				// �����_���������邽�߂ɒ񋟂��ꂽ�֐����Ăяo��
				f(a->GetOwner(), b->GetOwner());
			}
		}
	}
}

void PhysWorld::SweepAndPruneXYZ()
{
	// �܂�X���Ń\�[�g
	std::sort(mColliderXAxis.begin(), mColliderXAxis.end(),
		[](Collider* a, Collider* b) {
			return a->GetWorldBox().mMin.x < b->GetWorldBox().mMin.x;
		});

	mCurrentHitPairs.clear();

	// X���X�C�[�v�J�n
	for (size_t i = 0; i < mColliderXAxis.size(); ++i)
	{
		Collider* colliderA = mColliderXAxis[i];
		const AABB& aabbA = colliderA->GetWorldBox();

		for (size_t j = i + 1; j < mColliderXAxis.size(); ++j)
		{
			Collider* colliderB = mColliderXAxis[j];
			const AABB& aabbB = colliderB->GetWorldBox();

			const float contactOffset = 0.001f;

			/*
			// X���̍ő�ƍŏ����������ĂȂ�������break�i�������j
			// �� contactOffset ���������Ĕ�r
			if (aabbB.mMin.x - contactOffset > aabbA.mMax.x + contactOffset)
				break;

			// Y����Z���̌�������ɂ� contactOffset ���l��
			if (aabbA.mMax.y + contactOffset < aabbB.mMin.y - contactOffset ||
				aabbA.mMin.y - contactOffset > aabbB.mMax.y + contactOffset)
				continue;

			if (aabbA.mMax.z + contactOffset < aabbB.mMin.z - contactOffset ||
				aabbA.mMin.z - contactOffset > aabbB.mMax.z + contactOffset)
				continue;
			*/
			// X���̍ő�ƍŏ����������ĂȂ�������break�i�������j
			if (aabbB.mMin.x > aabbA.mMax.x)
				break;

			// Y����Z���̌�������ɂ� contactOffset ���l��
			if (aabbA.mMax.y < aabbB.mMin.y ||
				aabbA.mMin.y > aabbB.mMax.y)
				continue;

			if (aabbA.mMax.z < aabbB.mMin.z ||
				aabbA.mMin.z > aabbB.mMax.z)
				continue;

			// �����܂ŗ�����A��B�͓������Ă���
			auto actorA = colliderA->GetOwner();
			auto actorB = colliderB->GetOwner();

			std::pair<ActorObject*, ActorObject*> sortedPair = actorA < actorB ?
				std::make_pair(actorA, actorB) : std::make_pair(actorB, actorA);

			mCurrentHitPairs.emplace(sortedPair);

			// Enter or Stay����
			if (mPrevHitPairs.count(sortedPair))
			{
				actorA->OnCollisionStay(actorB);
				actorB->OnCollisionStay(actorA);
				//�����葱���Ă��鎞������
				if (!colliderA->IsStaticObject() && colliderB->IsStaticObject())
				{
					FixCollisions(colliderA, colliderB);
				}
				else if (colliderA->IsStaticObject() && !colliderB->IsStaticObject())
				{
					FixCollisions(colliderB, colliderA);
				}
			}
			else
			{
				actorA->OnCollisionEnter(actorB);
				actorB->OnCollisionEnter(actorA);
				//�����菉�߂ɔ���
				if (!colliderA->IsStaticObject() && colliderB->IsStaticObject())
				{
					FixCollisions(colliderA, colliderB);
				}
				else if (colliderA->IsStaticObject() && !colliderB->IsStaticObject())
				{
					FixCollisions(colliderB, colliderA);
				}
			}
		}
	}

	// Exit�`�F�b�N
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

	// ��ԍX�V
	mPrevHitPairs = mCurrentHitPairs;
}

void PhysWorld::FixCollisions(class Collider* dynamicCollider, class Collider* staticCollider)
{
	dynamicCollider->GetOwner()->ComputeWorldTransform(NULL);

	ActorObject* dynamicActor = dynamicCollider->GetOwner();
	Vector3 pos = dynamicActor->GetLocalPosition();
	
	// ���ʂ̈Ⴂ���v�Z
	float dx1 = staticCollider->GetWorldBox().mMax.x - dynamicCollider->GetWorldBox().mMin.x;
	float dx2 = staticCollider->GetWorldBox().mMin.x - dynamicCollider->GetWorldBox().mMax.x;
	float dy1 = staticCollider->GetWorldBox().mMax.y - dynamicCollider->GetWorldBox().mMin.y;
	float dy2 = staticCollider->GetWorldBox().mMin.y - dynamicCollider->GetWorldBox().mMax.y;
	float dz1 = staticCollider->GetWorldBox().mMax.z - dynamicCollider->GetWorldBox().mMin.z;
	float dz2 = staticCollider->GetWorldBox().mMin.z - dynamicCollider->GetWorldBox().mMax.z;

	// dx��dx1�܂���dx2�̂����A��Βl���Ⴂ���ɐݒ�B
	float dx = Math::Abs(dx1) < Math::Abs(dx2) ?
		dx1 : dx2;
	// dy�ɂ��Ă����l
	float dy = Math::Abs(dy1) < Math::Abs(dy2) ?
		dy1 : dy2;
	// dz�ɂ��Ă����l
	float dz = Math::Abs(dz1) < Math::Abs(dz2) ?
		dz1 : dz2;

	constexpr float skinWidth = 0.001f;

	Axis collisionAxis;
	// �ł��߂����ɉ�����x/y�ʒu�𒲐�
	if (Math::Abs(dx) < Math::Abs(dy) && Math::Abs(dx) < Math::Abs(dz))
	{
		pos.x += dx + Math::Sign(dx) * skinWidth;
		collisionAxis = X;
	}
	else if (Math::Abs(dy) < Math::Abs(dx) && Math::Abs(dy) < Math::Abs(dz))
	{
		pos.y += dy + Math::Sign(dy) * skinWidth;
		collisionAxis = Y;
	}
	else
	{
		pos.z += dz + Math::Sign(dz) * skinWidth;
		collisionAxis = Z;
	}

	// �|�W�V������ݒ肵�A�{�b�N�X�R���|�[�l���g���X�V����K�v������܂��B
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
	dynamicActor->SetPosition(pos);
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
		// �x�N�g���̖����ɃX���b�v���A
		// �|�b�v�I�t���܂��i�R�s�[�̏���������邽�߁j
		std::iter_swap(iter, mCollider.end() - 1);
		mCollider.pop_back();
	}

	iter = std::find(mColliderXAxis.begin(), mColliderXAxis.end(), box);
	if (iter != mColliderXAxis.end())
	{
		// �x�N�g���̖����ɃX���b�v���A
		// �|�b�v�I�t���܂��i�R�s�[�̏���������邽�߁j
		std::iter_swap(iter, mColliderXAxis.end() - 1);
		mColliderXAxis.pop_back();
	}

	iter = std::find(mColliderYAxis.begin(), mColliderYAxis.end(), box);
	if (iter != mColliderYAxis.end())
	{
		// �x�N�g���̖����ɃX���b�v���A
		// �|�b�v�I�t���܂��i�R�s�[�̏���������邽�߁j
		std::iter_swap(iter, mColliderYAxis.end() - 1);
		mColliderYAxis.pop_back();
	}

	iter = std::find(mColliderZAxis.begin(), mColliderZAxis.end(), box);
	if (iter != mColliderZAxis.end())
	{
		// �x�N�g���̖����ɃX���b�v���A
		// �|�b�v�I�t���܂��i�R�s�[�̏���������邽�߁j
		std::iter_swap(iter, mColliderZAxis.end() - 1);
		mColliderZAxis.pop_back();
	}
}
