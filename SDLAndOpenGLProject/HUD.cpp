#include "HUD.h"


HUD::HUD()
	:Canvas()
	, mRadarRange(2000.0f)
	, mRadarRadius(92.0f)
	, mTargetEnemy(false)
	, mCrosshairAngle(0)
{
	Renderer* r = mGame->GetWinMain()->GetRenderer();
	mRadar = new Image();
	mRadar->Load("Radar.png");

	mCrosshair = new Image();
	mCrosshair->Load("Crosshair.png");
	mCrosshair->SetFillMethod(Image::Radial360);

	mCrosshairEnemy = new Image();
	mCrosshairEnemy->Load("CrosshairRed.png");
	
	mBlipTex = new Image();
	mBlipTex->Load("Blip.png");

	mRadarArrow = new Image();
	mRadarArrow->Load("RadarArrow.png");


	mHelthBar = new Image();
	mHelthBar->Load("HelthBar.png");

	mHelthBarFrame = new Image();
	mHelthBarFrame->Load("HelthBarFrame.png");


	mHelthBar->SetFillMethod(Image::Horizontal);

	mHelthBarFrame->SetPosition(Vector2(-300,-300));
	mHelthBar->SetPosition(Vector2(-300,-300));
}

HUD::~HUD()
{
}

void HUD::Update(float deltaTime)
{
	Canvas::Update(deltaTime);

	UpdateCrosshair(deltaTime);
	UpdateRadar(deltaTime);

	//各画像の座標更新

	// Crosshair
	if (GameStateClass::mGameState == TimeStop) { return; }
	if (mTargetEnemy)
	{
		mCrosshair->SetState(Image::EClosing);
		mCrosshairEnemy->SetState(Image::EActive);
		mCrosshairEnemy->SetPosition(Vector2::Zero);
	}
	else
	{
		mCrosshairEnemy->SetState(Image::EClosing);
		mCrosshair->SetState(Image::EActive);
		mCrosshair->SetPosition(Vector2::Zero);
	}
	//Image* crosshair = mTargetEnemy ? mCrosshairEnemy : mCrosshair;
	//mCrosshairAngle++;
	//crosshair->SetAngleZ(mCrosshairAngle);
	//crosshair->SetScale(Vector3(1.5f, 0.5f,1.0f));


	// Radar
	const Vector2 cRadarPos(-390.0f, 275.0f);
	mRadar->SetPosition(cRadarPos);
	//mRadar->Draw(shader);
	// Blips
	for (Vector2& blip : mBlips)
	{
		blip *= 100.0f;
		mBlipTex->SetPosition(cRadarPos + blip);
	}

	// Radar arrow
	mRadarArrow->SetPosition(cRadarPos);
}

void HUD::ProcessInput(const InputState& keys)
{
	//テスト用入力
	if (keys.Keyboard.GetKey(KEY_DOWN))
	{
		float fill = mCrosshair->GetFillAmount();
		fill -= 0.01f;
		if (fill <= 0)
		{
			fill = 0;
		}
		mCrosshair->SetFillAmount(fill);
	}
	else if (keys.Keyboard.GetKey(KEY_UP))
	{
		float fill = mCrosshair->GetFillAmount();
		fill += 0.01f;
		if (fill >= 1)
		{
			fill = 1;
		}
		mCrosshair->SetFillAmount(fill);
	}
}

void HUD::AddTargetComponent(TargetComponent* tc)
{
	mTargetComps.emplace_back(tc);
}

void HUD::RemoveTargetComponent(TargetComponent* tc)
{
	auto iter = std::find(mTargetComps.begin(), mTargetComps.end(),
		tc);
	mTargetComps.erase(iter);
}

void HUD::UpdateCrosshair(float deltaTime)
{
	// Reset to regular cursor
	mTargetEnemy = false;
	// Make a line segment
	const float cAimDist = 500.0f;
	Vector3 start = Vector3::Zero;
	Vector3 dir = Vector3::Zero;
	mGame->GetWinMain()->GetRenderer()->GetScreenDirection(start, dir);
	LineSegment l(start, start + dir * cAimDist);
	// Segment cast
	PhysWorld::CollisionInfo info;
	if (mGame->GetPhysWorld()->RayCast(l, info))
	{
		// Is this a target?
		for (auto tc : mTargetComps)
		{
			if (tc->GetOwner()->GetActorTag() == info.mActor->GetActorTag())
			{
				mTargetEnemy = true;
				break;
			}
		}
	}
}

void HUD::UpdateRadar(float deltaTime)
{
	// Clear blip positions from last frame
	mBlips.clear();

	// Convert player position to radar coordinates (x forward, z up)
	Vector3 playerPos = mGame->GetPlayer()->GetLocalPosition();
	Vector2 playerPos2D(playerPos.x, playerPos.z);
	// Ditto for player forward
	Vector3 playerForward = mGame->GetPlayer()->GetForward();
	Vector2 playerForward2D(playerForward.z, playerForward.x);

	// Use atan2 to get rotation of radar
	float angle = Math::Atan2(playerForward2D.y, playerForward2D.x);
	// Make a 2D rotation matrix
	Matrix3 rotMat = Matrix3::CreateRotation(angle);

	// Get positions of blips
	for (auto tc : mTargetComps)
	{
		Vector3 targetPos = tc->GetOwner()->GetLocalPosition();
		Vector2 actorPos2D(targetPos.x, targetPos.z);

		// Calculate vector between player and target
		Vector2 playerToTarget = actorPos2D - playerPos2D;

		// See if within range
		if (playerToTarget.LengthSq() <= (mRadarRange * mRadarRange))
		{
			// Convert playerToTarget into an offset from
			// the center of the on-screen radar
			Vector2 blipPos = playerToTarget;
			blipPos *= mRadarRadius / mRadarRange;

			// Rotate blipPos
			blipPos = Vector2::Transform(blipPos, rotMat);
			mBlips.emplace_back(blipPos);
		}
	}
}