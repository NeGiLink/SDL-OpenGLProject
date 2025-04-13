#pragma once
#include "STD.h"
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
		class BoxCollider* mBox;
		// �R���|�[�l���g�̏��LActor
		class ActorObject*	mActor;
	};

	// �������{�b�N�X�ɑ΂��Ĕ��肵�܂��B
	// �{�b�N�X�ɏՓ˂���ꍇ�͐^��Ԃ��܂��B
	bool RayCast(const LineSegment& l, CollisionInfo& outColl);

	//�f�p��pairwise�Փ˔���
	void TestPairwise(std::function<void(class ActorObject*, class ActorObject*)> f);

	//sweepprune�g�p�����Փ˔���
	//void TestSweepAndPrune(std::function<void(class ActorObject*, class ActorObject*)> f);

	void SortColliderXAxis();
	void SortColliderYAxis();
	void SortColliderZAxis();

	//XYZ��Sweepprune���g�p�����Փ˔���
	void SweepAndPruneXYZ();

	// ���E����{�b�N�X�R���|�[�l���g��ǉ�/�폜����
	void AddBox(class BoxCollider* box);
	void RemoveBox(class BoxCollider* box);
private:
	class BaseScene* mGame;
	//����Box
	std::vector<class BoxCollider*> mBoxes;
	
	std::vector<class BoxCollider*> mBoxesXAxis;

	std::vector<class BoxCollider*> mBoxesYAxis;
	
	std::vector<class BoxCollider*> mBoxesZAxis;

	std::set<std::pair<BoxCollider*, BoxCollider*>> mHitBoxesXAxis;

	std::set<std::pair<BoxCollider*, BoxCollider*>> mHitBoxesYAxis;

	std::set<std::pair<BoxCollider*, BoxCollider*>> mHitBoxesZAxis;

	std::set<std::pair<ActorObject*, ActorObject*>> mPrevHitPairs;

	std::set<std::pair<ActorObject*, ActorObject*>> mCurrentHitPairs;

	//std::vector<class Collider*> mCollider;
};