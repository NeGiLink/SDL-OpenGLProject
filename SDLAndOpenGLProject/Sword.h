#pragma once
#include "Actor.h"
#include "MeshRenderer.h"
#include "BoxCollider.h"
#include "Mesh.h"
#include "Skeleton.h"
//剣オブジェクトのクラス
class Sword : public ActorObject
{
public:
						Sword();
	void				ActorInput(const struct InputState& keys) override;
private:

	Vector3				mPos;

	float				mAngleY;
	float				mAngleX;
	float				mAngleZ;
};

