#include "TargetComponent.h"
#include "Actor.h"
#include "WinMain.h"
#include "BaseScene.h"
#include "PhysWorld.h"
#include "Math.h"
#include "HUD.h"

TargetComponent::TargetComponent(ActorObject* owner)
	:Component(owner)
{
	mOwner->GetGame()->GetHUD()->AddTargetComponent(this);
}

TargetComponent::~TargetComponent()
{
	mOwner->GetGame()->GetHUD()->RemoveTargetComponent(this);
}