#include "TargetActor.h"
#include "WinMain.h"
#include "BaseScene.h"
#include "Renderer.h"
#include "MeshRenderer.h"
#include "BoxComponent.h"
#include "Mesh.h"
#include "TargetComponent.h"

TargetActor::TargetActor(BaseScene* game)
	:ActorObject(game)
{
	SetScale(100.0f);
	SetRotation(Quaternion(Vector3::UnitZ, Math::Pi));
	mMeshComp = new MeshRenderer(this);
	mMeshComp->SetMeshs(game->GetWinMain()->GetRenderer()->GetMeshs("Target.fbx"));

	// “–‚½‚è”»’è‹@”\’Ç‰Á
	for (unsigned int i = 0; i < mMeshComp->GetMeshs().size(); i++) 
	{
		for (unsigned int j = 0; j < mMeshComp->GetMeshs()[i]->GetBoxs().size(); j++)
		{
			BoxComponent* box = new BoxComponent(this);
			box->SetObjectBox(mMeshComp->GetMeshs()[i]->GetBoxs()[j]);
			mBoxs.push_back(box);
		}
	}
	new TargetComponent(this);

}