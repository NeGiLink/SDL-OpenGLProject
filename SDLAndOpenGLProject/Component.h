#pragma once
#include <cstdint>

class Component
{
public:
	// Constructor
	// (the lower the update order, the earlier the component updates)
	Component(class ActorObject* owner, int updateOrder = 100);
	// Destructor
	virtual ~Component();
	// Update this component by delta time
	virtual void Update(float deltaTime);
	// Process input for this component
	virtual void ProcessInput(const bool* keyState) {}
	// Called when world transform changes
	virtual void OnUpdateWorldTransform() { }

	class ActorObject* GetOwner() { return mOwner; }
	int GetUpdateOrder() const { return mUpdateOrder; }
protected:
	// Owning actor
	class ActorObject* mOwner;
	// Update order of component
	int mUpdateOrder;
};