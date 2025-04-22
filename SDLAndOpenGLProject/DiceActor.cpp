#include "DiceActor.h"
#include "WinMain.h"
#include "BaseScene.h"
#include "Renderer.h"
#include "MeshRenderer.h"
#include "BoxCollider.h"
#include "Mesh.h"

DiceActor::DiceActor()
	:ActorObject()
{
	MeshRenderer* mc = new MeshRenderer(this);
	Mesh* mesh = GetGame()->GetWinMain()->GetRenderer()->GetMesh("TestCube.fbx");
	mc->SetMesh(mesh);
	/*
	// Add collision box
	for (unsigned int i = 0; i < mc->GetMeshs().size(); i++) {
		// ボックスの当たり判定機能追加
		for (unsigned int j = 0; j < mc->GetMeshs()[i]->GetBoxs().size(); j++)
		{
			BoxCollider* box = new BoxCollider(this);
			box->SetObjectBox(mc->GetMeshs()[i]->GetBoxs()[j]);
			mBoxs.push_back(box);
		}
	}
	*/
	//SetScale(50.0f);
}

void DiceActor::UpdateActor(float deltaTime)
{
}

void DiceActor::ActorInput(const struct InputState& keys)
{
	/*
	bool input = false;
	Vector3 pos;
	if(keys.Keyboard.GetKeyUp(SDL_SCANCODE_LSHIFT))
	{
		pos.y += 1.0f;
		input = true;
	}
	else if (keys.Keyboard.GetKeyUp(SDL_SCANCODE_RCTRL))
	{
		pos.y -= 1.0f;
		input = true;
	}

	if (keys.Keyboard.GetKeyUp(SDL_SCANCODE_RIGHT))
	{
		pos.x += 1.0f;
		input = true;
	}
	else if (keys.Keyboard.GetKeyUp(SDL_SCANCODE_LEFT))
	{
		pos.x -= 1.0f;
		input = true;
	}

	if (keys.Keyboard.GetKeyUp(SDL_SCANCODE_UP))
	{
		pos.z += 1.0f;
		input = true;
	}
	else if (keys.Keyboard.GetKeyUp(SDL_SCANCODE_DOWN))
	{
		pos.z -= 1.0f;
		input = true;
	}
	Quaternion rot;
	if (keys.Keyboard.GetKey(SDL_SCANCODE_Y))
	{
		mRotationAmountY += 0.1f;
		input = true;
	}
	else if (keys.Keyboard.GetKey(SDL_SCANCODE_H))
	{
		mRotationAmountY -= 0.1f;
		input = true;
	}

	if (keys.Keyboard.GetKey(SDL_SCANCODE_T))
	{
		mRotationAmountX += 0.1f;
		input = true;
	}
	else if (keys.Keyboard.GetKey(SDL_SCANCODE_G))
	{
		mRotationAmountX -= 0.1f;
		input = true;
	}

	if (keys.Keyboard.GetKey(SDL_SCANCODE_U))
	{
		mRotationAmountZ += 0.1f;
		input = true;
	}
	else if (keys.Keyboard.GetKey(SDL_SCANCODE_J))
	{
		mRotationAmountZ -= 0.1f;
		input = true;
	}
	Vector3 scale = GetScale();
	if (keys.Keyboard.GetKeyDown(SDL_SCANCODE_M))
	{
		scale += 1.0f;
		input = true;
	}
	else if (keys.Keyboard.GetKeyDown(SDL_SCANCODE_N))
	{
		scale -= 1.0f;
		input = true;
	}
	if (!input) { return; }
	rot = Quaternion(Vector3::UnitX, mRotationAmountX);
	rot *= Quaternion(Vector3::UnitY, mRotationAmountY);
	rot *= Quaternion(Vector3::UnitZ, mRotationAmountZ);
	SetRotation(rot);
	AddPosition(pos);
	SetScale(scale);
	*/
}

void DiceActor::OnCollisionEnter(ActorObject* target)
{
	//SDL_Log("Dice Hit!");
}
