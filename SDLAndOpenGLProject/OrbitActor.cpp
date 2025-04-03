#include "OrbitActor.h"
#include "MeshRenderer.h"
#include "WinMain.h"
#include "BaseScene.h"
#include "Renderer.h"
#include "OrbitCamera.h"
#include "MoveComponent.h"

OrbitActor::OrbitActor(BaseScene* game)
	:ActorObject(game)
{
	mMeshComp = new MeshRenderer(this);
	mMeshComp->SetMesh(game->GetWinMain()->GetRenderer()->GetMesh("Assets/RacingCar.gpmesh"));
	SetPosition(Vector3(0.0f, 0.0f, -100.0f));

	mCameraComp = new OrbitCamera(this);
}

void OrbitActor::ActorInput(const bool* keys)
{
	// Mouse rotation
	// Get relative movement from SDL
	float x, y;
	Uint64 buttons = SDL_GetRelativeMouseState(&x, &y);
	// Only apply rotation if right-click is held
	if (buttons & SDL_BUTTON_MASK(SDL_BUTTON_RIGHT))
	{
		// Assume mouse movement is usually between -500 and +500
		const int maxMouseSpeed = 500;
		// Rotation/sec at maximum speed
		const float maxOrbitSpeed = Math::Pi * 8;
		float yawSpeed = 0.0f;
		if (x != 0)
		{
			// Convert to ~[-1.0, 1.0]
			yawSpeed = static_cast<float>(x) / maxMouseSpeed;
			// Multiply by rotation/sec
			yawSpeed *= maxOrbitSpeed;
		}
		mCameraComp->SetYawSpeed(-yawSpeed);

		// Compute pitch
		float pitchSpeed = 0.0f;
		if (y != 0)
		{
			// Convert to ~[-1.0, 1.0]
			pitchSpeed = static_cast<float>(y) / maxMouseSpeed;
			pitchSpeed *= maxOrbitSpeed;
		}
		mCameraComp->SetPitchSpeed(pitchSpeed);
	}
}

void OrbitActor::SetVisible(bool visible)
{
	mMeshComp->SetVisible(visible);
}