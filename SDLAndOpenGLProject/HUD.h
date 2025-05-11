#pragma once
#include "UIScreen.h"
#include "PhysWorld.h"
#include "TargetComponent.h"
#include "Actor.h"

//ゲーム上のUIをまとめて処理するクラス
class HUD : public UIScreen
{
public:
	// (下に引く順序は後ろに対応します)
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

	// ゲーム内のすべてのターゲットコンポーネント
	vector<class TargetComponent*>			mTargetComps;
	// レーダーに対するブリップの2Dオフセット
	vector<Vector2>							mBlips;
	// レーダーの範囲と半径を調整する
	float									mRadarRange;
	float									mRadarRadius;
	// クロスヘアが敵を狙っているかどうか
	bool									mTargetEnemy;
	
	float									mCrosshairAngle;
};

