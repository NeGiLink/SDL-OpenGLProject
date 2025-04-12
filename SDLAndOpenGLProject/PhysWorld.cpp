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
	// closestT�𖳌���ɏ��������āA
	// �ŏ��̌����_�����closestT���X�V����悤�ɂ��܂��B
	float closestT = Math::Infinity;
	Vector3 norm;
	// ���ׂẴ{�b�N�X�ɑ΂��锻��
	for (auto box : mBoxes)
	{
		float t;
		// ���̐����̓{�b�N�X�ƌ������Ă��邩����
		if (Intersect(l, box->GetWorldBox(), t, norm))
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
			BoxComponent* a = mBoxes[i];
			BoxComponent* b = mBoxes[j];
			if (Intersect(a->GetWorldBox(), b->GetWorldBox()))
			{
				// �����_���������邽�߂ɒ񋟂��ꂽ�֐����Ăяo��
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
		// ���݂̃{�b�N�X�ɑ΂���max.x���擾����
		BoxComponent* a = mBoxes[i];
		float max = a->GetWorldBox().mMax.x;
		for (size_t j = i + 1; j < mBoxes.size(); j++)
		{
			BoxComponent* b = mBoxes[j];
			// AABB[j]�̍ŏ��l��AABB[i]�̍ő�l�𒴂��Ă���ꍇ�A
			// AABB[i]�Ƃ̌����͑��ɑ��݂��Ȃ�����break
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
		// �x�N�g���̖����ɃX���b�v���A
		// �|�b�v�I�t���܂��i�R�s�[�̏���������邽�߁j
		std::iter_swap(iter, mBoxes.end() - 1);
		mBoxes.pop_back();
	}
}