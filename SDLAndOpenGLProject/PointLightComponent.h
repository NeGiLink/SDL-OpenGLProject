#pragma once
#include "Math.h"
#include "Component.h"

class PointLightComponent : public Component
{
public:
	PointLightComponent(class ActorObject* owner);
	~PointLightComponent();

	// Draw this point light as geometry
	void Draw(class Shader* shader, class Mesh* mesh);

	// Diffuse color
	Vector3 mDiffuseColor;
	// Radius of light
	float mInnerRadius;
	float mOuterRadius;
};

