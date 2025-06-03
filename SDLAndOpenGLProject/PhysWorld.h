#pragma once
#include "StandardLibrary.h"
#include "Math.h"
#include "Collision.h"

//���Е��������������t�@�C��
//���ׂẴI�u�W�F�N�g�̏Փ˔�����Ǘ����Ă���N���X
//Unity�̓����蔻��̏Փ˔��蕔���݂����ȋ@�\
class PhysWorld
{
public:
	enum Axis
	{
		X,
		Y,
		Z
	};

	// �Փˌ��ʂɊւ�������܂Ƃ߂Ă���
	struct CollisionInfo
	{
		// �Փ˓_
		Vector3				mPoint;
		// �Փˎ��̍��W
		Vector3				mNormal;
		float				mT;
		// �Փ˃N���X
		class Collider*		mCollider;
		// �R���|�[�l���g�̏��LActor
		class ActorObject*	mActor;
	};

	struct ContactPoint
	{
		Vector3 normal;        // �ڐG�@��
		float penetration;     // �߂荞�ݐ[��
	};

private:
	class BaseScene*									mGame;

	vector<class Collider*>								mCollider;

	vector<class Collider*>								mColliderXAxis;

	vector<class Collider*>								mColliderYAxis;

	vector<class Collider*>								mColliderZAxis;

	std::set<std::pair<Collider*, Collider*>>			mHitColliderXAxis;

	std::set<std::pair<Collider*, Collider*>>			mHitColliderYAxis;

	std::set<std::pair<Collider*, Collider*>>			mHitColliderZAxis;


	std::set<std::pair<ActorObject*, ActorObject*>>		mPrevHitPairs;

	std::set<std::pair<ActorObject*, ActorObject*>>		mCurrentHitPairs;

public:

														PhysWorld(class BaseScene* game);

	// �������{�b�N�X�ɑ΂��Ĕ��肵�܂��B
	// �{�b�N�X�ɏՓ˂���ꍇ�͐^��Ԃ��܂��B
	bool												RayCast(const LineSegment& l, CollisionInfo& outColl);
	vector<CollisionInfo>								RayCastAll(const LineSegment& l);

	//�f�p��pairwise�Փ˔���
	void												TestPairwise(std::function<void(class ActorObject*, class ActorObject*)> f);

	//XYZ��Sweepprune���g�p�����Փ˔���
	void												SweepAndPruneXYZ();

	void												FixCollisions(class Collider* dynamicCollider, class Collider* staticCollider);
	//AABB�ł̉����o���Ɏg�p����֐�
	bool												GetContactInfo(const AABB& a, const AABB& b, Vector3& outNormal, float& outDepth);

	void												CollectContactPoints(const AABB& a, const AABB& b, std::vector<ContactPoint>& outContacts, float contactOffset);
	Vector3												CalculatePushVector(const std::vector<ContactPoint>& contacts, float contactOffset);
	//OBB�ł̉����o���Ɏg�p����֐�
	/*
	void												CollectContactPoints(const OBB& a, const OBB& b, std::vector<ContactPoint>& outContacts, float contactOffset);
	
	bool												GetContactInfo_OBB(const OBB& a, const OBB& b, Vector3& outNormal, float& outDepth);

	bool												OnCollision_OBB(const OBB& a, const OBB& b);

	bool												TestAxis(const Vector3& axis, const OBB& a, const OBB& b);

	void												ProjectOBB(const OBB& obb, const Vector3& axis, float& outMin, float& outMax);
	*/
	// ���E����{�b�N�X�R���|�[�l���g��ǉ�/�폜����
	void												AddCollider(class Collider* box);
	void												RemoveCollider(class Collider* box);
};