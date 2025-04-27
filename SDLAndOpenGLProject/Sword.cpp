#include "Sword.h"


Sword::Sword()
	:ActorObject()
{
	
	MeshRenderer* mc = new MeshRenderer(this);
	Mesh* mesh = GetGame()->GetWinMain()->GetRenderer()->GetMesh("Sword.fbx");
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
	*/
	Vector3 scale = GetLocalScale();
	if (keys.Keyboard.GetKey(SDL_SCANCODE_M))
	{
		scale += 0.1f;
	}
	else if (keys.Keyboard.GetKey(SDL_SCANCODE_N))
	{
		scale -= 0.1f;
	}
	SetScale(scale);
}
