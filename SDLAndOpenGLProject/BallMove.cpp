#include "BallMove.h"
#include "Actor.h"
#include "BaseScene.h"
#include "PhysWorld.h"
#include "TargetActor.h"
#include "BallActor.h"

BallMove::BallMove(ActorObject* owner)
	:MoveComponent(owner)
{
}

void BallMove::Update(float deltaTime)
{
	// �ړ������ɉ����ăZ�O�����g���\�z����
	const float segmentLength = 30.0f;
	Vector3 start = mOwner->GetLocalPosition();
	Vector3 dir = mOwner->GetForward();
	Vector3 end = start + dir * segmentLength;

	// �������쐬����
	LineSegment l(start, end);
	//TODO : �����ƃ{�b�N�X�����蔻��
	// �e�X�g�Z�O�����g�ΐ��E
	PhysWorld* phys = mOwner->GetGame()->GetPhysWorld();
	PhysWorld::CollisionInfo info;
	// (�v���C���[�ƏՓ˂��Ȃ�)
	if (phys->RayCast(l, info) && info.mActor != mPlayer)
	{
		// �����Փ˂�����A�@���ɑ΂��ă{�[���𔽎�
		dir = Vector3::Reflect(dir, info.mNormal);
		mOwner->RotateToNewForward(dir);
		// �^�[�Q�b�g�ɏՓ˂������ǂ���
		TargetActor* target = dynamic_cast<TargetActor*>(info.mActor);
		if (target)
		{
			static_cast<BallActor*>(mOwner)->HitTarget();
		}
	}

	// ���N���X�̃A�b�v�f�[�g�͑O���̑��x�Ɋ�Â��Ĉړ����܂�
	MoveComponent::Update(deltaTime);
}
