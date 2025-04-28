#pragma once
#include "StandardLibrary.h"
#include "Math.h"
#include "Collision.h"

//���ׂẴI�u�W�F�N�g�̏Փ˔�����Ǘ����Ă���N���X
//Unity�̓����蔻��̏Փ˔��蕔���݂����ȋ@�\
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
		// �Փ˃N���X
		class Collider*		mCollider;
		// �R���|�[�l���g�̏��LActor
		class ActorObject*	mActor;
	};

	// �������{�b�N�X�ɑ΂��Ĕ��肵�܂��B
	// �{�b�N�X�ɏՓ˂���ꍇ�͐^��Ԃ��܂��B
	bool RayCast(const LineSegment& l, CollisionInfo& outColl);

	//�f�p��pairwise�Փ˔���
	void TestPairwise(std::function<void(class ActorObject*, class ActorObject*)> f);

	//XYZ��Sweepprune���g�p�����Փ˔���
	void SweepAndPruneXYZ();

	void FixCollisions(class Collider* dynamicCollider, class Collider* staticCollider);

	// ���E����{�b�N�X�R���|�[�l���g��ǉ�/�폜����
	void AddCollider(class Collider* box);
	void RemoveCollider(class Collider* box);
private:
	class BaseScene*									mGame;

	std::vector<class Collider*>						mCollider;

	std::vector<class Collider*>						mColliderXAxis;

	std::vector<class Collider*>						mColliderYAxis;

	std::vector<class Collider*>						mColliderZAxis;

	std::set<std::pair<Collider*, Collider*>>			mHitColliderXAxis;

	std::set<std::pair<Collider*, Collider*>>			mHitColliderYAxis;

	std::set<std::pair<Collider*, Collider*>>			mHitColliderZAxis;


	std::set<std::pair<ActorObject*, ActorObject*>>		mPrevHitPairs;

	std::set<std::pair<ActorObject*, ActorObject*>>		mCurrentHitPairs;
};