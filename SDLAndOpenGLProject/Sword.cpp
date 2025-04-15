#include "Sword.h"
#include "WinMain.h"
#include "BaseScene.h"
#include "Renderer.h"
#include "MeshRenderer.h"
#include "BoxCollider.h"
#include "Mesh.h"

Sword::Sword(BaseScene* game)
	:ActorObject(game)
{
	SetScale(Vector3(100.0f, 100.0f, 100.0f));
	
	MeshRenderer* mc = new MeshRenderer(this);
	Mesh* mesh = game->GetWinMain()->GetRenderer()->GetMesh("Sword.fbx");
	mc->SetMesh(mesh);
}

void Sword::ActorInput(const struct InputState& keys)
{
	/*
	Vector3 pos;
	if (keys[SDL_SCANCODE_SPACE]) 
	{
		pos.y += 10.0f;
	}
	else if(keys[SDL_SCANCODE_LSHIFT])
	{
		pos.y -= 10.0f;
	}

	if (keys[SDL_SCANCODE_RIGHT])
	{
		pos.x += 10.0f;
	}
	else if (keys[SDL_SCANCODE_LEFT])
	{
		pos.x -= 10.0f;
	}

	if (keys[SDL_SCANCODE_UP])
	{
		pos.z += 10.0f;
	}
	else if (keys[SDL_SCANCODE_DOWN])
	{
		pos.z -= 10.0f;
	}
	Quaternion rot;
	if (keys[SDL_SCANCODE_Y])
	{
		mAngleY += 0.1f;
	}
	else if (keys[SDL_SCANCODE_H])
	{
		mAngleY -= 0.1f;
	}

	if (keys[SDL_SCANCODE_X])
	{
		mAngleX += 0.1f;
	}
	else if (keys[SDL_SCANCODE_C])
	{
		mAngleX -= 0.1f;
	}

	if (keys[SDL_SCANCODE_Z])
	{
		mAngleZ += 0.1f;
	}
	else if (keys[SDL_SCANCODE_Q])
	{
		mAngleZ -= 0.1f;
	}
	Vector3 scale = GetScale();
	if (keys[SDL_SCANCODE_M])
	{
		scale *= 1.5f;
	}
	else if (keys[SDL_SCANCODE_N])
	{
		scale *= 0.5f;
	}
	
	rot = Quaternion(Vector3::UnitX, mAngleX);
	rot *= Quaternion(Vector3::UnitY, mAngleY);
	rot *= Quaternion(Vector3::UnitZ, mAngleZ);
	SetRotation(rot);
	AddPosition(pos);
	SetScale(scale);
	*/
}

void Sword::UpdateRightHand(Skeleton::Bone* hand)
{
	SetPosition(hand->mLocalBindPose.mPosition);
	SetRotation(hand->mLocalBindPose.mRotation);
}
