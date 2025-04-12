#include "FPSActor.h"
#include "MoveComponent.h"
#include <SDL3/SDL_scancode.h>
#include "Renderer.h"
#include "AudioSystem.h"
#include "WinMain.h"
#include "BaseScene.h"
#include "AudioComponent.h"
#include "FPSCamera.h"
#include "MeshRenderer.h"
#include "BallActor.h"
#include "BoxComponent.h"
#include "PlaneActor.h"
#include "Sword.h"

FPSActor::FPSActor(BaseScene* game)
	:ActorObject(game)
{
	mMoveComp = new MoveComponent(this);
	mAudioComp = new AudioComponent(this);
	mLastFootstep = 0.0f;
	mFootstep = mAudioComp->PlayEvent("event:/Footstep");
	mFootstep.SetPaused(true);

	mCameraComp = new FPSCamera(this);

	// ボックスの当たり判定の機能を追加
	mBoxComp = new BoxComponent(this);
	AABB myBox(Vector3(-25.0f, -87.5f, -25.0f),
		Vector3(25.0f, 87.5f, 25.0f));
	mBoxComp->SetObjectBox(myBox);
	mBoxComp->SetShouldRotate(false);

	mSword = new Sword(game);
	Vector3 pos = GetPosition();
	mSword->SetPosition(pos);
	AddChildActor(mSword);
}

void FPSActor::UpdateActor(float deltaTime)
{
	ActorObject::UpdateActor(deltaTime);

	FixCollisions();

	// 足音のSEを再生する処理
	mLastFootstep -= deltaTime;
	if ((!Math::NearZero(mMoveComp->GetForwardSpeed()) ||
		!Math::NearZero(mMoveComp->GetStrafeSpeed())) &&
		mLastFootstep <= 0.0f)
	{
		mFootstep.SetPaused(false);
		mFootstep.Restart();
		mLastFootstep = 0.5f;
	}
}

void FPSActor::ActorInput(const bool* keys)
{
	float forwardSpeed = 0.0f;
	float strafeSpeed = 0.0f;
	// wasd movement
	if (keys[SDL_SCANCODE_W])
	{
		forwardSpeed += 400.0f;
	}
	if (keys[SDL_SCANCODE_S])
	{
		forwardSpeed -= 400.0f;
	}
	if (keys[SDL_SCANCODE_A])
	{
		strafeSpeed -= 400.0f;
	}
	if (keys[SDL_SCANCODE_D])
	{
		strafeSpeed += 400.0f;
	}

	mMoveComp->SetForwardSpeed(forwardSpeed);
	mMoveComp->SetStrafeSpeed(strafeSpeed);

	//SDLでマウスの移動数値を取得
	float x, y;
	SDL_GetRelativeMouseState(&x, &y);
	//マウスでの最大移動数値を設定
	const int maxMouseSpeed = 500;
	// 最大速度での回転/秒
	const float maxAngularSpeed = Math::Pi * 8;
	float angularSpeed = 0.0f;
	if (x != 0)
	{
		// [-1.0, 1.0]に変換する
		angularSpeed = static_cast<float>(x) / maxMouseSpeed;
		// 回転/秒で掛ける
		angularSpeed *= maxAngularSpeed;
	}
	mMoveComp->SetAngularSpeed(angularSpeed);

	// 音高を計算する
	const float maxPitchSpeed = Math::Pi * 8;
	float pitchSpeed = 0.0f;
	if (y != 0)
	{
		// [-1.0, 1.0]に変換する
		pitchSpeed = static_cast<float>(y) / maxMouseSpeed;
		pitchSpeed *= maxPitchSpeed;
	}
	mCameraComp->SetPitchSpeed(pitchSpeed);

	//子オブジェクトを解除・セットする処理(テスト用)
	if (keys[SDL_SCANCODE_O]) 
	{
		RemoveChildActor(mSword);
	}
	else if (keys[SDL_SCANCODE_P]) 
	{
		AddChildActor(mSword);
	}
}

void FPSActor::Shoot()
{
	// スタートポイントを取得する（近くの平面の画面の中心）
	Vector3 screenPoint(0.0f, 0.0f, 0.0f);
	Vector3 start = GetGame()->GetWinMain()->GetRenderer()->Unproject(screenPoint);
	// 画面の中央、近くと遠くの間にエンドポイントを取得します。
	screenPoint.z = 0.9f;
	Vector3 end = GetGame()->GetWinMain()->GetRenderer()->Unproject(screenPoint);
	// 方向ベクトルを取得する
	Vector3 dir = end - start;
	dir.Normalize();
	// ボールを生成する
	BallActor* ball = new BallActor(GetGame());
	ball->SetPlayer(this);
	ball->SetPosition(start + dir * 20.0f);
	// ボールを回転させて新しい方向を向ける
	ball->RotateToNewForward(dir);
	// 発射音を再生する
	mAudioComp->PlayEvent("event:/Shot");
}

void FPSActor::SetFootstepSurface(float value)
{
	//ここで一時停止します。
	// FMODでパラメーターを設定した方法を変更すると、足音が再生されるため
	mFootstep.SetPaused(true);
	mFootstep.SetParameter("Surface", value);
}

void FPSActor::SetVisible(bool visible)
{
	mMeshComp->SetVisible(visible);
}

void FPSActor::FixCollisions()
{
	// ワールドボックスを更新するために、ワールド変換を再計算する必要があります。
	ComputeWorldTransform();

	const AABB& playerBox = mBoxComp->GetWorldBox();
	Vector3 pos = GetPosition();

	auto& planes = GetGame()->GetPlanes();
	for (auto pa : planes)
	{
		for (unsigned int i = 0; i < pa->GetBoxs().size(); i++) {
			//PlaneActorと衝突検知
			const AABB& planeBox = pa->GetBoxs()[i]->GetWorldBox();
			if (Intersect(playerBox, planeBox))
			{
				// 私たちのすべての違いを計算してください
				float dx1 = planeBox.mMax.x - playerBox.mMin.x;
				float dx2 = planeBox.mMin.x - playerBox.mMax.x;
				float dy1 = planeBox.mMax.y - playerBox.mMin.y;
				float dy2 = planeBox.mMin.y - playerBox.mMax.y;
				float dz1 = planeBox.mMax.z - playerBox.mMin.z;
				float dz2 = planeBox.mMin.z - playerBox.mMax.z;

				// dxをdx1またはdx2のうち、絶対値が低い方に設定します。
				float dx = Math::Abs(dx1) < Math::Abs(dx2) ?
					dx1 : dx2;
				// dyについても同様です
				float dy = Math::Abs(dy1) < Math::Abs(dy2) ?
					dy1 : dy2;
				// dzについても同様です
				float dz = Math::Abs(dz1) < Math::Abs(dz2) ?
					dz1 : dz2;

				// 最も近い方に応じてx/y位置を調整する
				if (Math::Abs(dx) <= Math::Abs(dy) && Math::Abs(dx) <= Math::Abs(dz))
				{
					pos.x += dx;
				}
				else if (Math::Abs(dy) <= Math::Abs(dx) && Math::Abs(dy) <= Math::Abs(dz))
				{
					pos.y += dy;
				}
				else
				{
					pos.z += dz;
				}

				// ポジションを設定し、ボックスコンポーネントを更新する必要があります。
				SetPosition(pos);
				mBoxComp->OnUpdateWorldTransform();
			}

		}
	}
}