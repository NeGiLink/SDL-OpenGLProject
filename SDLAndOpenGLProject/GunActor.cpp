#include "GunActor.h"

GunActor::GunActor()
	:ActorObject()
{
	mGunMesh = new MeshActor();
	mGunMesh->Load("TestGun.fbx");
	mGunMesh->SetLocalScale(Vector3(0.2f, 0.2f, 0.2f));
	AddChildActor(mGunMesh);
}

void GunActor::FixedUpdateActor(float deltaTime)
{
}

void GunActor::UpdateActor(float deltaTime)
{
}

void GunActor::ActorInput(const InputState& keys)
{
	if (keys.Mouse.GetButtonDown(SDL_BUTTON_LEFT))
	{
		Fire();
	}
}

void GunActor::Fire()
{
	Vector3 screenPos, screenDir;
	mGame->GetWinMain()->GetRenderer()->GetScreenDirection(screenPos, screenDir);

	// Make a line segment
	const float cAimDist = 100.0f;

	LineSegment l(screenPos, screenPos + screenDir * cAimDist);
	// Segment cast
	PhysWorld::CollisionInfo info;
	ActorTag tag = ActorTag::Ground;
	Vector3 targetPoint;
	if (mGame->GetPhysWorld()->RayCast(l, info))
	{
		targetPoint = info.mPoint;
	}
	else
	{
		targetPoint = l.mStart + l.mEnd; // �͂��Ȃ��Ƃ��͉���
	}

	Vector3 direction = (targetPoint - mPosition).Normalized();
	BulletActor* bullet = new BulletActor(direction, mPosition);

}
