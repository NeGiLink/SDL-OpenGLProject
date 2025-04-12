#pragma once
#include <vector>
#include <functional>
#include "Math.h"
#include "Collision.h"

class PhysWorld
{
public:
	PhysWorld(class BaseScene* game);

	// �Փˌ��ʂɊւ�������܂Ƃ߂Ă���
	struct CollisionInfo
	{
		// �Փ˓_
		Vector3				mPoint;
		// �Փˎ��̍��W
		Vector3				mNormal;
		// �{�b�N�X�Փ˃N���X
		class BoxComponent* mBox;
		// �R���|�[�l���g�̏��LActor
		class ActorObject*	mActor;
	};

	// �������{�b�N�X�ɑ΂��Ĕ��肵�܂��B
	// �{�b�N�X�ɏՓ˂���ꍇ�͐^��Ԃ��܂��B
	bool SegmentCast(const LineSegment& l, CollisionInfo& outColl);

	//�f�p��pairwise�Փ˔���
	void TestPairwise(std::function<void(class ActorObject*, class ActorObject*)> f);

	//sweepprune�g�p�����Փ˔���
	void TestSweepAndPrune(std::function<void(class ActorObject*, class ActorObject*)> f);

	// ���E����{�b�N�X�R���|�[�l���g��ǉ�/�폜����
	void AddBox(class BoxComponent* box);
	void RemoveBox(class BoxComponent* box);
private:
	class BaseScene* mGame;
	std::vector<class BoxComponent*> mBoxes;
};