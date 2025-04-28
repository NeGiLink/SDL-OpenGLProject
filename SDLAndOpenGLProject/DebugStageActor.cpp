#include "DebugStageActor.h"

DebugStageActor::DebugStageActor()
	:ActorObject()
{
	//�^�O�w��
	mActorTag = ActorTag::Ground;
	mMeshComp = new MeshRenderer(this);
	mMeshComp->SetMeshs(GetGame()->GetWinMain()->GetRenderer()->GetMeshs("DebugStage.fbx"));

	for (unsigned int i = 0; i < mMeshComp->GetMeshs().size(); i++) {
		// �{�b�N�X�̓����蔻��@�\�ǉ�
		for (unsigned int j = 0; j < mMeshComp->GetMeshs()[i]->GetBoxs().size(); j++)
		{
			BoxCollider* box = new BoxCollider(this);
			box->SetObjectBox(mMeshComp->GetMeshs()[i]->GetBoxs()[j]);
			mBoxs.push_back(box);
		}
	}
}
