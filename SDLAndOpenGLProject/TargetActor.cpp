#include "TargetActor.h"


TargetActor::TargetActor()
	:ActorObject()
{
	mActorTag = ActorTag::Enemy;
	SetLocalRotation(Quaternion(Vector3::UnitZ, Math::Pi));
	mMeshComp = new MeshRenderer(this);
	mMeshComp->SetMeshs(GetGame()->GetWinMain()->GetRenderer()->GetMeshs("Target.fbx"));

	// 当たり判定機能追加
	for (unsigned int i = 0; i < mMeshComp->GetMeshs().size(); i++) 
	{
		for (unsigned int j = 0; j < mMeshComp->GetMeshs()[i]->GetBoxs().size(); j++)
		{
			BoxCollider* box = new BoxCollider(this);
			box->SetObjectBox(mMeshComp->GetMeshs()[i]->GetBoxs()[j]);
			mBoxs.push_back(box);
		}
	}
	new TargetComponent(this);

}