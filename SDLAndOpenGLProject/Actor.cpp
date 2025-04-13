#include "Actor.h"
#include "BaseScene.h"
#include "Component.h"
#include <algorithm>

ActorObject::ActorObject(BaseScene* game)
	:mState(EActive)
	, mPosition(Vector3::Zero)
	, mRotation(Quaternion::Identity)
	, mScale(Vector3(1.0f,1.0f,1.0f))
	, mGame(game)
	, mRecomputeWorldTransform(true)
{
	mGame->AddActor(this);
}

ActorObject::~ActorObject()
{
	mGame->RemoveActor(this);
	// Need to delete components
	// Because ~Component calls RemoveComponent, need a different style loop
	while (!mComponents.empty())
	{
		delete mComponents.back();
	}
}

void ActorObject::Update(float deltaTime)
{
	if (mState == EActive)
	{
		ComputeWorldTransform();

		UpdateComponents(deltaTime);
		UpdateActor(deltaTime);

		ComputeWorldTransform();
	}
}

void ActorObject::UpdateComponents(float deltaTime)
{
	for (auto comp : mComponents)
	{
		comp->Update(deltaTime);
	}
}

void ActorObject::UpdateActor(float deltaTime)
{

	for (auto child : mChildActor) 
	{
		child->SetActive();
	}
}

void ActorObject::ProcessInput(const bool* keyState)
{
	if (mState == EActive)
	{
		// First process input for components
		for (auto comp : mComponents)
		{
			comp->ProcessInput(keyState);
		}

		ActorInput(keyState);
	}
}

void ActorObject::ActorInput(const bool* keyState)
{
}

void ActorObject::ComputeWorldTransform()
{
	if (mRecomputeWorldTransform)
	{
		mRecomputeWorldTransform = false;
		// Scale, then rotate, then translate
		// 親がいれば親のワールド行列を適用（ローカル→ワールド）
		if (mParentActor)
		{
			Vector3 worldScale = mParentActor->GetScale() * mScale;
			Quaternion worldRotation = mParentActor->GetRotation() * mRotation;
			// 3. ローカル位置を親のスケール分で拡大
			Vector3 localPositionScaled = mParentActor->GetScale() * mPosition;

			// 4. ローカル位置を親の回転で回す（親の向きを尊重）
			Vector3 localPositionRotated = mParentActor->GetRotation().RotateVector(localPositionScaled);

			// 5. ワールド座標を親の位置 + 相対位置で決定
			Vector3 worldPosition = mParentActor->GetPosition() + localPositionRotated;

			mWorldTransform = Matrix4::CreateScale(worldScale);
			mWorldTransform *= Matrix4::CreateFromQuaternion(worldRotation);
			mWorldTransform *= Matrix4::CreateTranslation(worldPosition);
		}
		else 
		{
			mWorldTransform = Matrix4::CreateScale(mScale);
			mWorldTransform *= Matrix4::CreateFromQuaternion(mRotation);
			mWorldTransform *= Matrix4::CreateTranslation(mPosition);
		}
		// Inform components world transform updated
		for (auto comp : mComponents)
		{
			comp->OnUpdateWorldTransform();
		}
	}
}

void ActorObject::RotateToNewForward(const Vector3& forward)
{
	// Figure out difference between original (unit x) and new
	float dot = Vector3::Dot(Vector3::UnitX, forward);
	float angle = Math::Acos(dot);
	// Facing down X
	if (dot > 0.9999f)
	{
		SetRotation(Quaternion::Identity);
	}
	// Facing down -X
	else if (dot < -0.9999f)
	{
		SetRotation(Quaternion(Vector3::UnitZ, Math::Pi));
	}
	else
	{
		// Rotate about axis from cross product
		Vector3 axis = Vector3::Cross(Vector3::UnitX, forward);
		axis.Normalize();
		SetRotation(Quaternion(axis, angle));
	}
}

void ActorObject::AddComponent(Component* component)
{
	// Find the insertion point in the sorted vector
	// (The first element with a order higher than me)
	int myOrder = component->GetUpdateOrder();
	auto iter = mComponents.begin();
	for (;
		iter != mComponents.end();
		++iter)
	{
		if (myOrder < (*iter)->GetUpdateOrder())
		{
			break;
		}
	}

	// Inserts element before position of iterator
	mComponents.insert(iter, component);
}

void ActorObject::RemoveComponent(Component* component)
{
	auto iter = std::find(mComponents.begin(), mComponents.end(), component);
	if (iter != mComponents.end())
	{
		mComponents.erase(iter);
	}
}

void ActorObject::AddChildActor(ActorObject* actor)
{
	for (ActorObject* a : mChildActor) {
		if (a == actor) { return; }
	}
	actor->SetParentActor(this);
	mChildActor.push_back(actor);
}

void ActorObject::RemoveChildActor(ActorObject* actor)
{
	auto iter = std::find(mChildActor.begin(), mChildActor.end(), actor);
	if (iter != mChildActor.end())
	{
		actor->SetParentActor(nullptr);
		mChildActor.erase(iter);
	}
}

const ActorObject* ActorObject::GetChildActor(ActorObject* actor)
{
	for (ActorObject* a : mChildActor) {
		if (a == actor) {
			return a;
		}
	}
	return nullptr;
}
