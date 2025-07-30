#pragma once
#include "Component.h"
#include "Shader.h"
#include "Actor.h"

//書籍元を改造したファイル
//環境光の構造体
struct DirectionalLightData
{
	// Direction of light
	Vector3 mDirection;
	// Diffuse color
	Vector3 mDiffuseColor;
	// Ambient color
	Vector3 mAmbientColor;
	// Specular color
	Vector3 mSpecColor;
	//位置
	Vector3 mPosition;
};
//環境光の機能
class DirectionalLightComponent : public Component
{
private:
	DirectionalLightData mDirectionalLight;
public:
	DirectionalLightComponent(class ActorObject* owner);
	~DirectionalLightComponent();
	void OnUpdateWorldTransform()override;

	DirectionalLightData GetDirectionalLight() const { return mDirectionalLight; }  
};