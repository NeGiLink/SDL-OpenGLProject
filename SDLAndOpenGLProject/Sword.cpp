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
	Vector3 scale = GetLocalScale();
	if (keys.Keyboard.GetKey(SDL_SCANCODE_M))
	{
		scale += 0.1f;
	}
	else if (keys.Keyboard.GetKey(SDL_SCANCODE_N))
	{
		scale -= 0.1f;
	}
	SetLocalScale(scale);
}
