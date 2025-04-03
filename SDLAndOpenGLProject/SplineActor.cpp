#include "SplineActor.h"
#include "MeshRenderer.h"
#include "WinMain.h"
#include "BaseScene.h"
#include "Renderer.h"
#include "SplineCamera.h"
#include "MoveComponent.h"

SplineActor::SplineActor(BaseScene* game)
	:ActorObject(game)
{
	//MeshRenderer* mc = new MeshRenderer(this);
	//mc->SetMesh(game->GetRenderer()->GetMesh("Assets/RacingCar.gpmesh"));
	//SetPosition(Vector3(0.0f, 0.0f, -100.0f));

	mCameraComp = new SplineCamera(this);

	// Create a spline
	Spline path;
	path.mControlPoints.emplace_back(Vector3::Zero);
	for (int i = 0; i < 5; i++)
	{
		if (i % 2 == 0)
		{
			path.mControlPoints.emplace_back(Vector3(300.0f * (i + 1), 300.0f, 300.0f));
		}
		else
		{
			path.mControlPoints.emplace_back(Vector3(300.0f * (i + 1), 0.0f, 0.0f));
		}
	}

	mCameraComp->SetSpline(path);
	mCameraComp->SetPaused(false);
}

void SplineActor::ActorInput(const bool* keys)
{

}

void SplineActor::RestartSpline()
{
	mCameraComp->Restart();
}