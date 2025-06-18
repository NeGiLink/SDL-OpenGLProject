#include "CubeActor.h"

CubeActor::CubeActor()
	:ActorObject()
{
	MeshRenderer* mc = new MeshRenderer(this);
	vector<class Mesh*> mesh = GetGame()->GetWinMain()->GetRenderer()->GetMeshs("Cube.fbx");
	mc->SetMeshs(mesh);


	BoxCollider* box = new BoxCollider(this);
	box->SetObjectOBB(mc->GetMeshs()[0]->GetOBBBoxs()[0]);
	mBox = box;
}
