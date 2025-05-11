#pragma once
#include "UIScreen.h"
#include "PhysWorld.h"
#include "TargetComponent.h"
#include "Actor.h"

//�Q�[�����UI���܂Ƃ߂ď�������N���X
class HUD : public UIScreen
{
public:
	// (���Ɉ��������͌��ɑΉ����܂�)
	HUD();
	~HUD();

	void Update(float deltaTime) override;
	void Draw(class Shader* shader) override;

	void AddTargetComponent(class TargetComponent* tc);
	void RemoveTargetComponent(class TargetComponent* tc);
protected:
	void UpdateCrosshair(float deltaTime);
	void UpdateRadar(float deltaTime);

	class Image*							mRadar;

	class Image*							mCrosshair;
	class Image*							mCrosshairEnemy;
	
	class Image*							mBlipTex;
	
	class Image*							mRadarArrow;

	// �Q�[�����̂��ׂẴ^�[�Q�b�g�R���|�[�l���g
	vector<class TargetComponent*>			mTargetComps;
	// ���[�_�[�ɑ΂���u���b�v��2D�I�t�Z�b�g
	vector<Vector2>							mBlips;
	// ���[�_�[�͈̔͂Ɣ��a�𒲐�����
	float									mRadarRange;
	float									mRadarRadius;
	// �N���X�w�A���G��_���Ă��邩�ǂ���
	bool									mTargetEnemy;
	
	float									mCrosshairAngle;
};

