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
	bool												RayCast(const LineSegment& l, CollisionInfo& outColl,int tag);

	std::vector<CollisionInfo>							RayCastAll(const LineSegment& l);

	//XYZ��Sweepprune���g�p�����Փ˔���
	void												SweepAndPruneXYZ();
	//�����o�������̌Ăяo����
	void												FixCollisions(class Collider* dynamicCollider, class Collider* staticCollider);
	//�e�R���C�_�[���m�̐���������܂Ƃ߂��֐�
	bool												IsOnCollision(class Collider* colliderA, class Collider* colliderB);
	//�e�R���C�_�[���m�̉����o���������܂Ƃ߂��֐�
	void												IsCollectContactPoints(class Collider* colliderA, class Collider* colliderB, std::vector<ContactPoint>& outContacts, float contactOffset);

	//OBB vs OBB�̉����o������
	void												CollectContactPoints_OBB_OBB(const OBB& a, const OBB& b, std::vector<ContactPoint>& outContacts, float contactOffset);
	//OBB vs OBB�̉����o�������Ɏg���֐�
	bool												GetContactInfo_OBB(const OBB& a, const OBB& b, Vector3& outNormal, float& outDepth);
	//Sphere vs Sphere�̉����o������
	void												CollectContactPoints_Sphere_Sphere(const Sphere& a, const Sphere& b, std::vector<ContactPoint>& outContacts, float contactOffset);
	//Capsule vs Capsule�̉����o������
	void												CollectContactPoints_Capsule_Capsule(const Capsule& a, const Capsule& b, std::vector<ContactPoint>& outContacts, float contactOffset);
	//OBB vs Sphere�̉����o������
	void												CollectContactPoints_OBB_Sphere(const OBB& a, const Sphere& b, std::vector<ContactPoint>& outContacts, float contactOffset);
	//OBB vs Capsule�̉����o������
	void												CollectContactPoints_OBB_Capsule(const OBB& a, const Capsule& b, std::vector<ContactPoint>& outContacts, float contactOffset);
	//Sphere vs Capsule�̉����o������
	void												CollectContactPoints_Sphere_Capsule(const Sphere& a, const Capsule& b, std::vector<ContactPoint>& outContacts, float contactOffset);

	// ���E����{�b�N�X�R���|�[�l���g��ǉ�/�폜����
	void												AddCollider(class Collider* box);
	void												RemoveCollider(class Collider* box);
};