#include "Component.h"
#include "Actor.h"

Component::Component(ActorObject* owner, int updateOrder)
	:mOwner(owner)
	, mUpdateOrder(updateOrder)
	, mGame(owner->GetGame())
{
	// Actor�̃R���|�[�l���g�x�N�g���ɒǉ�����
	mOwner->AddComponent(this);
}

Component::~Component()
{
	mOwner->RemoveComponent(this);
}

void Component::Update(float deltaTime)
{
}