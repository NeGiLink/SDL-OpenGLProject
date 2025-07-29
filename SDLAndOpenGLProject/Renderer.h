#pragma once
#include "SDL3.h"
#include "Typedefs.h"

/*
* ===エンジン内部処理/Engine internal processing===
*/

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
// 3D描画のレンダラー
class Renderer
{
private:
	//3D描画処理
	void												Draw3DScene(unsigned int framebuffer, const Matrix4& view, const Matrix4& proj,
		float viewPortScale = 1.0f, bool lit = true);
	//ライト描画処理
	void												DrawFromGBuffer();
	//Shaderの読み込み
	bool												LoadShaders();
	//Spriteの頂点を作成
	void												CreateSpriteVerts();
	//扇型スプライトの頂点を作成
	int 												CreateFanSpriteVerts(float fillRatio /*0.0～1.0: 扇の割合*/, int segments);
	//LineSpriteの頂点を作成
	//現在は未使用
	void												CreateLineSpriteVerts();
	//オブジェクトの方向矢印の頂点を作成
	void 												CreateAxisVerts();

	//ライトのShader、マトリックスのSetter
	void												SetLightUniforms(class Shader* shader, const Matrix4& view);
	// テクスチャのマップが読み込み変数
	std::unordered_map<string, class Texture*>			mTextures;
	// メッシュの地図がロード
	std::unordered_map<string, class Mesh*>				mMeshes;
	// 描かれたすべてのスプライトコンポーネント
	vector<class SpriteComponent*>						mSprites;
	// すべての（骨格以外の）メッシュコンポーネント
	vector<class MeshRenderer*>							mMeshComps;
	vector<class SkeletalMeshRenderer*>					mSkeletalMeshes;
	vector<class ParticleSystem*>						mParticlesComps;
	// BaseScene
	class BaseScene*									mNowScene;
	//***Shader***
	// Sprite shader
	class Shader*										mSpriteShader;
	// Sprite vertex array
	class VertexArray*									mSpriteVerts;
	//2D画像用の頂点配列
	class VertexArray*									mFanSpriteVerts;
	//オブジェクトの方向矢印用の頂点配列
	class VertexArray*									mAxisVAO;

	//パーティクルシェーダー
	class Shader*										mParticleShader;

	// Mesh shader
	class Shader*										mMeshShader;
	// Skinned shader
	class Shader*										mSkinnedShader;
	class Shader*										mArrowShader;

	// View/projection for 3D shaders
	Matrix4												mView;
	Matrix4												mProjection;

	// Lighting data
	DirectionalLightData								mDirLight;
	// Window
	SDL_Window*											mWindow;
	// OpenGL context
	SDL_GLContext										mContext;


	class GBuffer*										mGBuffer;
	// GBuffer shader
	class Shader*										mGGlobalShader;
	class Shader*										mGPointLightShader;
	vector<class PointLightComponent*>					mPointLights;
	class Mesh*											mPointLightMesh;

	class DebugGrid*									mDebugGrid;

	class Shader*										mGridShader;
public:
														Renderer(class GameWinMain* game);
														~Renderer();

	bool												Initialize(float screenWidth, float screenHeight);
	//描画部分のアンロード(Shaderなど)
	void												Shutdown();
	//シーン別に保存しているオブジェクトをアンロードする処理
	void												UnloadData();
	void												MeshOrderUpdate();
	//描画処理
	void												Draw();
	//スプライト追加処理
	void												AddSprite(class SpriteComponent* sprite);
	//スプライト削除処理
	void												RemoveSprite(class SpriteComponent* sprite);
	//Mesh追加処理
	void												AddMeshComp(class MeshRenderer* mesh);
	//Mesh削除処理
	void												RemoveMeshComp(class MeshRenderer* mesh);
	//Mesh追加処理
	void												AddParticleComp(class ParticleSystem* particle);
	//Mesh削除処理
	void												RemoveParticleComp(class ParticleSystem* particle);
	//PointLight追加処理
	void												AddPointLight(class PointLightComponent* light);
	//PointLight削除処理
	void												RemovePointLight(class PointLightComponent* light);
	//PointLightMeshの設定処理
	void												SetPointLightMesh(class Mesh* mesh) { mPointLightMesh = mesh; }
	//TextureのGetter
	class Texture*										GetTexture(const string& fileName);
	//MeshのGetter
	class Mesh*											GetMesh(const string& fileName);
	//Mesh配列のGetter
	vector<class Mesh*>									GetMeshs(const string& fileName);

	Matrix4												GetView() { return mView; }
	//カメラのビュー行列のSetter
	void												SetViewMatrix(const Matrix4& view) { mView = view; }
	//DirLightのGetter
	DirectionalLightData&								GetDirectionalLight() { return mDirLight; }
	//DirLightのSetter
	void												SetDirectionalLight(DirectionalLightData& dirLight) { mDirLight = dirLight; }
	// Given a screen space point, unprojects it into world space,
	// based on the current 3D view/projection matrices
	// Expected ranges:
	// x = [-screenWidth/2, +screenWidth/2]
	// y = [-screenHeight/2, +screenHeight/2]
	// z = [0, 1) -- 0 is closer to camera, 1 is further
	// スクリーン座標からワールド座標への変換
	Vector3												Unproject(const Vector3& screenPoint) const;
	//スクリーンの方向を取得
	void												GetScreenDirection(Vector3& outStart, Vector3& outDir) const;
	//GBufferのGetter
	class GBuffer*										GetGBuffer() { return mGBuffer; }
	// Mesh shader
	class Shader*										GetMeshShader() { return mMeshShader; }
	// Skinned shader
	class Shader*										GetSkinnedShader() { return mSkinnedShader; }
	//BaseSceneのGetter
	void												SetBaseScene(class BaseScene* scene) { mNowScene = scene; }
	//mWindowのGetter
	SDL_Window*											GetWindow() { return mWindow; }
};