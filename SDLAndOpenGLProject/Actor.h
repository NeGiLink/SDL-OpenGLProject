#pragma once

#include <vector>
#include "Math.h"
#include <cstdint>

class ActorObject
{
public:
	enum State
	{
		EActive,
		EPaused,
		EDead
	};

	ActorObject(class BaseScene* game);
	virtual ~ActorObject();

	// Update function called from Game (not overridable)
	void Update(float deltaTime);
	// Updates all the components attached to the actor (not overridable)
	void UpdateComponents(float deltaTime);
	// Any actor-specific update code (overridable)
	virtual void UpdateActor(float deltaTime);

	// ProcessInput function called from Game (not overridable)
	void ProcessInput(const bool* keyState);
	// Any actor-specific input code (overridable)
	virtual void ActorInput(const bool* keyState);

	// Getters/setters
	const Vector3& GetPosition() const { return mPosition; }

	void SetPosition(const Vector3& pos) { mPosition = pos; mRecomputeWorldTransform = true; }
	
	Vector3 GetScale() const { return mScale; }
	
	void SetScale(Vector3 scale) { mScale = scale;  mRecomputeWorldTransform = true; }
	
	void SetScale(float scale) { mScale = Vector3(scale,scale,scale);  mRecomputeWorldTransform = true; }
	
	const Quaternion& GetRotation() const { return mRotation; }
	
	void SetRotation(const Quaternion& rotation) { mRotation = rotation;  mRecomputeWorldTransform = true; }

	void ComputeWorldTransform();
	
	const Matrix4& GetWorldTransform() const { return mWorldTransform; }

	Vector3 GetForward() const { return Vector3::Transform(Vector3::UnitZ, mRotation); }
	
	Vector3 GetRight() const { return Vector3::Transform(Vector3::UnitX, mRotation); }

	void RotateToNewForward(const Vector3& forward);

	State GetState() const { return mState; }
	
	void SetState(State state) { mState = state; }

	class BaseScene* GetGame() { return mGame; }


	// Add/remove components
	void AddComponent(class Component* component);
	
	void RemoveComponent(class Component* component);
	//子オブジェクトを追加
	void AddChildActor(class ActorObject* actor);
	
	void RemoveChildActor(class ActorObject* actor);
	
	const class ActorObject* GetChildActor(class ActorObject* actor);
	
	void SetParentActor(class ActorObject* parent) { mParentActor = parent; }
private:
	// Transform
	Matrix4 mWorldTransform;
protected:
	// Actor's state
	State mState;

	Vector3 mPosition;

	Quaternion mRotation;

	Vector3 mScale;

	bool mRecomputeWorldTransform;

	std::vector<class Component*> mComponents;

	class ActorObject* mParentActor;

	std::vector<class ActorObject*> mChildActor;

	class BaseScene* mGame;
};