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
	// closestT�𖳌���ɏ��������āA
	// �ŏ��̌����_�����closestT���X�V����悤�ɂ��܂��B
	float closestT = Math::Infinity;
	Vector3 norm;
	// ���ׂẴ{�b�N�X�ɑ΂��锻��
	for (auto box : mBoxes)
	{
		float t;
		// ���̐����̓{�b�N�X�ƌ������Ă��邩����
		if (OnCollision(l, box->GetWorldBox(), t, norm))
		{
			// ����͈ȑO�̌����_���߂���
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
	// �P���Ȏ��� O(n^2)
	for (size_t i = 0; i < mBoxes.size(); i++)
	{
		// �������g��ȑO��i�l�ɑ΂��ăe�X�g����K�v�͂Ȃ�
		for (size_t j = i + 1; j < mBoxes.size(); j++)
		{
			BoxCollider* a = mBoxes[i];
			BoxCollider* b = mBoxes[j];
			if (OnCollision(a->GetWorldBox(), b->GetWorldBox()))
			{
				// �����_���������邽�߂ɒ񋟂��ꂽ�֐����Ăяo��
				f(a->GetOwner(), b->GetOwner());
			}
		}
	}
}

//X��Ver
void PhysWorld::SortColliderXAxis()
{

	for (size_t i = 0; i < mBoxes.size(); i++)
	{
		// ���݂̃{�b�N�X�ɑ΂���max.x���擾����
		BoxCollider* a = mBoxes[i];
		float max = a->GetWorldBox().mMax.x;
		for (size_t j = i + 1; j < mBoxes.size(); j++)
		{
			BoxCollider* b = mBoxes[j];
			// AABB[j]�̍ŏ��l��AABB[i]�̍ő�l�𒴂��Ă���ꍇ�A
			// AABB[i]�Ƃ̌����͑��ɑ��݂��Ȃ�����break
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
//Y��Ver
void PhysWorld::SortColliderYAxis()
{

	for (size_t i = 0; i < mBoxes.size(); i++)
	{
		// ���݂̃{�b�N�X�ɑ΂���max.x���擾����
		BoxCollider* a = mBoxes[i];
		float max = a->GetWorldBox().mMax.y;
		for (size_t j = i + 1; j < mBoxes.size(); j++)
		{
			BoxCollider* b = mBoxes[j];
			// AABB[j]�̍ŏ��l��AABB[i]�̍ő�l�𒴂��Ă���ꍇ�A
			// AABB[i]�Ƃ̌����͑��ɑ��݂��Ȃ�����break
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
//Z��Ver
void PhysWorld::SortColliderZAxis()
{

	for (size_t i = 0; i < mBoxes.size(); i++)
	{
		// ���݂̃{�b�N�X�ɑ΂���max.x���擾����
		BoxCollider* a = mBoxes[i];
		float max = a->GetWorldBox().mMax.z;
		for (size_t j = i + 1; j < mBoxes.size(); j++)
		{
			BoxCollider* b = mBoxes[j];
			// AABB[j]�̍ŏ��l��AABB[i]�̍ő�l�𒴂��Ă���ꍇ�A
			// AABB[i]�Ƃ̌����͑��ɑ��݂��Ȃ�����break
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
	// �܂�X���Ń\�[�g
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

	// �e���̔���
	mHitBoxesXAxis.clear();
	mHitBoxesYAxis.clear();
	mHitBoxesZAxis.clear();

	SortColliderXAxis();
	SortColliderYAxis();
	SortColliderZAxis();

	mCurrentHitPairs.clear();

	// ���ʃy�A�̌��o
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
		// �x�N�g���̖����ɃX���b�v���A
		// �|�b�v�I�t���܂��i�R�s�[�̏���������邽�߁j
		std::iter_swap(iter, mBoxes.end() - 1);
		mBoxes.pop_back();
	}

	iter = std::find(mBoxesXAxis.begin(), mBoxesXAxis.end(), box);
	if (iter != mBoxesXAxis.end())
	{
		// �x�N�g���̖����ɃX���b�v���A
		// �|�b�v�I�t���܂��i�R�s�[�̏���������邽�߁j
		std::iter_swap(iter, mBoxesXAxis.end() - 1);
		mBoxesXAxis.pop_back();
	}

	iter = std::find(mBoxesYAxis.begin(), mBoxesYAxis.end(), box);
	if (iter != mBoxesYAxis.end())
	{
		// �x�N�g���̖����ɃX���b�v���A
		// �|�b�v�I�t���܂��i�R�s�[�̏���������邽�߁j
		std::iter_swap(iter, mBoxesYAxis.end() - 1);
		mBoxesYAxis.pop_back();
	}

	iter = std::find(mBoxesZAxis.begin(), mBoxesZAxis.end(), box);
	if (iter != mBoxesZAxis.end())
	{
		// �x�N�g���̖����ɃX���b�v���A
		// �|�b�v�I�t���܂��i�R�s�[�̏���������邽�߁j
		std::iter_swap(iter, mBoxesZAxis.end() - 1);
		mBoxesZAxis.pop_back();
	}


}