#pragma once
#include "Actor.h"
#include "MeshRenderer.h"
#include "BoxCollider.h"
#include "Mesh.h"

//3Dモデルを読み込むクラス
//スケルトン無しの3Dモデルを
//読み込みだけのクラス
//ActorObjectを継承しているので1オブジェクトとしてカウント
class MeshActor : public ActorObject
{
private:
	MeshRenderer*				mMeshRenderer;

	vector<class BoxCollider*>	mBoxs;
public:
	void Load(string filePath);

	void SetTrigger(bool active);
};

