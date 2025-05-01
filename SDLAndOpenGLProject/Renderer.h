
#pragma once
#include "SDL3.h"
#include "Typedefs.h"

struct DirectionalLight
{
	// Direction of light
	Vector3 mDirection;
	// Diffuse color
	Vector3 mDiffuseColor;
	// Specular color
	Vector3 mSpecColor;
};

class Renderer
{
public:
	Renderer(class GameWinMain* game);
	~Renderer();

	bool Initialize(float screenWidth, float screenHeight);
	//描画部分のアンロード(Shaderなど)
	void Shutdown();
	//シーン別に保存しているオブジェクトをアンロードする処理
	void UnloadData();

	void Draw();

	void AddSprite(class SpriteComponent* sprite);
	void RemoveSprite(class SpriteComponent* sprite);
	//未完成
	void AddLineSprite(class LineRenderer* sprite);
	void RemoveLineSprite(class LineRenderer* sprite);

	void AddMeshComp(class MeshRenderer* mesh);
	void RemoveMeshComp(class MeshRenderer* mesh);

	void AddPointLight(class PointLightComponent* light);
	void RemovePointLight(class PointLightComponent* light);

	void SetPointLightMesh(class Mesh* mesh) { mPointLightMesh = mesh; }

	class Texture* GetTexture(const string& fileName);
	class Mesh* GetMesh(const string& fileName);
	vector<class Mesh*> GetMeshs(const string& fileName);

	void SetViewMatrix(const Matrix4& view) { mView = view; }

	void SetAmbientLight(const Vector3& ambient) { mAmbientLight = ambient; }
	DirectionalLight& GetDirectionalLight() { return mDirLight; }

	void SetDirectionalLight(DirectionalLight& dirLight) { mDirLight = dirLight; }

	// Given a screen space point, unprojects it into world space,
	// based on the current 3D view/projection matrices
	// Expected ranges:
	// x = [-screenWidth/2, +screenWidth/2]
	// y = [-screenHeight/2, +screenHeight/2]
	// z = [0, 1) -- 0 is closer to camera, 1 is further
	Vector3 Unproject(const Vector3& screenPoint) const;
	void GetScreenDirection(Vector3& outStart, Vector3& outDir) const;
	float GetScreenWidth() const { return mScreenWidth; }
	float GetScreenHeight() const { return mScreenHeight; }

	void SetMirrorView(const Matrix4& view) { mMirrorView = view; }
	class Texture* GetMirrorTexture() { return mMirrorTexture; }
	class GBuffer* GetGBuffer() { return mGBuffer; }

	// Mesh shader
	class Shader* GetMeshShader() { return mMeshShader; }
	// Skinned shader
	class Shader* GetSkinnedShader() { return mSkinnedShader; }

	void SetBaseScene(class BaseScene* scene) { mNowScene = scene; }

	SDL_Window* GetWindow() { return mWindow; }

private:
	void Draw3DScene(unsigned int framebuffer, const Matrix4& view, const Matrix4& proj,
		float viewPortScale = 1.0f, bool lit = true);
	bool CreateMirrorTarget();
	void DrawFromGBuffer();

	bool LoadShaders();
	void CreateSpriteVerts();
	void CreateLineSpriteVerts();
	void SetLightUniforms(class Shader* shader, const Matrix4& view);

	// テクスチャのマップが読み込み変数
	std::unordered_map<string, class Texture*>		mTextures;
	// メッシュの地図がロード
	std::unordered_map<string, class Mesh*>		mMeshes;

	// 描かれたすべてのスプライトコンポーネント
	vector<class SpriteComponent*>					mSprites;
	//未使用
	vector<class LineRenderer*>					mLineSprites;

	// すべての（骨格以外の）メッシュコンポーネント
	vector<class MeshRenderer*>					mMeshComps;
	vector<class SkeletalMeshRenderer*>			mSkeletalMeshes;

	// Game
	class GameWinMain*									mGame;

	class BaseScene*									mNowScene;

	//***Shader***
	// Sprite shader
	class Shader*										mSpriteShader;
	// Sprite vertex array
	class VertexArray*									mSpriteVerts;

	// Mesh shader
	class Shader*										mMeshShader;
	// Skinned shader
	class Shader*										mSkinnedShader;

	// View/projection for 3D shaders
	Matrix4												mView;
	Matrix4												mProjection;

	// Lighting data
	Vector3												mAmbientLight;
	DirectionalLight									mDirLight;

	// Window
	SDL_Window*											mWindow;
	// OpenGL context
	SDL_GLContext										mContext;
	// Width/height
	float												mScreenWidth;
	float												mScreenHeight;

	unsigned int										mMirrorBuffer;
	class Texture*										mMirrorTexture;
	Matrix4												mMirrorView;

	class GBuffer*										mGBuffer;
	// GBuffer shader
	class Shader*										mGGlobalShader;
	class Shader*										mGPointLightShader;
	vector<class PointLightComponent*>				mPointLights;
	class Mesh*											mPointLightMesh;
	/*
	//Line Shader
	class Shader*										mLineShader;
	// Sprite vertex array
	class VertexArray*									mLineSpriteVerts;
	*/
};