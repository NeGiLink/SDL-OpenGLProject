#pragma once
#include "Math.h"
#include "Component.h"

/*
* ===エンジン内部処理/Engine internal processing===
*/

//前方宣言
class Shader;
class Mesh;

//書籍部分
//ポイントライトの処理を行うクラス
class PointLightComponent : public Component
{
public:
			PointLightComponent(ActorObject* owner);
			~PointLightComponent();

	// このポイントライトを描画
	void	Draw(Shader* shader, Mesh* mesh);

	// Diffuse color
	Vector3 mDiffuseColor;
	// Radius of light
	float	mInnerRadius;
	float	mOuterRadius;
};

