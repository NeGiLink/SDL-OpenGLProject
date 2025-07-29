#include "DirectionalLightComponent.h"

DirectionalLightComponent::DirectionalLightComponent(ActorObject* owner)
	: Component(owner)
	, mDirectionalLight()
{
    mDirectionalLight.mDirection = Vector3(0.0f, -0.707f, -0.707f);
    mDirectionalLight.mDiffuseColor = Vector3(0.78f, 0.88f, 1.0f);
    mDirectionalLight.mSpecColor = Vector3(0.8f, 0.8f, 0.8f);
}

DirectionalLightComponent::~DirectionalLightComponent()
{
}

void DirectionalLightComponent::OnUpdateWorldTransform()
{
    // ライトベクトルの基準軸（太陽が右から左に動く＝X軸方向）
    Vector3 baseDir = Vector3::UnitX;

    // 回転を適用してライトの最終的な方向を得る（ワールド空間）
    Vector3 lightDir = Vector3::Transform(baseDir, mOwner->GetRotation());
    lightDir.Normalize();

    // ライト方向を保存
    mDirectionalLight.mDirection = lightDir;

    // ライトのY成分（太陽の高さ）を使って環境光を調整
    float sunHeight = lightDir.y; // y = 1:真上, y = 0:水平, y = -1:真下

    // 昼夜の補間
    Vector3 dayColor(0.7f, 0.7f, 0.6f);
    Vector3 nightColor(0.05f, 0.05f, 0.1f);

    float t = Math::Clamp(sunHeight, 0.0f, 1.0f); // 昼0〜1で補間
    Vector3 ambient = nightColor * (1.0f - t) + dayColor * t;

    // 最終的にライトに適用（例）
    mDirectionalLight.mAmbientColor = ambient;
    mDirectionalLight.mPosition = mOwner->GetPosition();

	mGame->GetWinMain()->GetRenderer()->SetDirectionalLight(mDirectionalLight);
}
