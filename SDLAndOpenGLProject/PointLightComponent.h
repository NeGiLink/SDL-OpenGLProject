#pragma once
#include "Math.h"
#include "Component.h"

/*
* ===�G���W����������/Engine internal processing===
*/

//���Е���
//�|�C���g���C�g�̏������s���N���X
class PointLightComponent : public Component
{
public:
			PointLightComponent(class ActorObject* owner);
			~PointLightComponent();

	// ���̃|�C���g���C�g��`��
	void	Draw(class Shader* shader, class Mesh* mesh);

	// Diffuse color
	Vector3 mDiffuseColor;
	// Radius of light
	float	mInnerRadius;
	float	mOuterRadius;
};

