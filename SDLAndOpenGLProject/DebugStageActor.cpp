#include "DebugStageActor.h"

DebugStageActor::DebugStageActor()
	:ActorObject()
{
	//タグ指定
	mActorTag = ActorTag::Ground;
	mMeshComp = new MeshRenderer(this);
	mMeshComp->SetMeshs(GetGame()->GetWinMain()->GetRenderer()->GetMeshs("DebugStage.fbx"));

	for (unsigned int i = 0; i < mMeshComp->GetMeshs().size(); i++) {
		// ボックスの当たり判定機能追加
		for (unsigned int j = 0; j < mMeshComp->GetMeshs()[i]->GetBoxs().size(); j++)
		{
			BoxCollider* box = new BoxCollider(this);
			box->SetObjectBox(mMeshComp->GetMeshs()[i]->GetBoxs()[j]);
			mBoxs.push_back(box);
		}
	}
}
