
#pragma once
#include "SDL3.h"
#include "Typedefs.h"

//�����̍\����
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

	bool												Initialize(float screenWidth, float screenHeight);
	//�`�敔���̃A�����[�h(Shader�Ȃ�)
	void												Shutdown();
	//�V�[���ʂɕۑ����Ă���I�u�W�F�N�g���A�����[�h���鏈��
	void												UnloadData();
	//�`�揈��
	void												Draw();
	//�X�v���C�g�ǉ�����
	void												AddSprite(class SpriteComponent* sprite);
	//�X�v���C�g�폜����
	void												RemoveSprite(class SpriteComponent* sprite);
	//������
	void												AddLineSprite(class LineRenderer* sprite);
	void												RemoveLineSprite(class LineRenderer* sprite);
	//Mesh�ǉ�����
	void												AddMeshComp(class MeshRenderer* mesh);
	//Mesh�폜����
	void												RemoveMeshComp(class MeshRenderer* mesh);
	//PointLight�ǉ�����
	void												AddPointLight(class PointLightComponent* light);
	//PointLight�폜����
	void												RemovePointLight(class PointLightComponent* light);
	//PointLightMesh�̐ݒ菈��
	void												SetPointLightMesh(class Mesh* mesh) { mPointLightMesh = mesh; }
	//Texture��Getter
	class Texture*										GetTexture(const string& fileName);
	//Mesh��Getter
	class Mesh*											GetMesh(const string& fileName);
	//Mesh�z���Getter
	vector<class Mesh*>									GetMeshs(const string& fileName);
	//�J�����̃r���[�s���Setter
	void												SetViewMatrix(const Matrix4& view) { mView = view; }
	//AmbientLight��Setter
	void												SetAmbientLight(const Vector3& ambient) { mAmbientLight = ambient; }
	//DirLight��Getter
	DirectionalLight&									GetDirectionalLight() { return mDirLight; }
	//DirLight��Setter
	void												SetDirectionalLight(DirectionalLight& dirLight) { mDirLight = dirLight; }
	// Given a screen space point, unprojects it into world space,
	// based on the current 3D view/projection matrices
	// Expected ranges:
	// x = [-screenWidth/2, +screenWidth/2]
	// y = [-screenHeight/2, +screenHeight/2]
	// z = [0, 1) -- 0 is closer to camera, 1 is further
	// �X�N���[�����W���烏�[���h���W�ւ̕ϊ�
	Vector3												Unproject(const Vector3& screenPoint) const;
	//�X�N���[���̕������擾
	void												GetScreenDirection(Vector3& outStart, Vector3& outDir) const;
	//��ʉ��T�C�Y�擾
	float												GetScreenWidth() const { return mScreenWidth; }
	//��ʏc�T�C�Y�擾
	float												GetScreenHeight() const { return mScreenHeight; }
	//GBuffer��Getter
	class GBuffer*										GetGBuffer() { return mGBuffer; }
	// Mesh shader
	class Shader*										GetMeshShader() { return mMeshShader; }
	// Skinned shader
	class Shader*										GetSkinnedShader() { return mSkinnedShader; }
	//BaseScene��Getter
	void												SetBaseScene(class BaseScene* scene) { mNowScene = scene; }
	//mWindow��Getter
	SDL_Window*											GetWindow() { return mWindow; }
private:
	//3D�`�揈��
	void												Draw3DScene(unsigned int framebuffer, const Matrix4& view, const Matrix4& proj,
														float viewPortScale = 1.0f, bool lit = true);
	//���C�g�`�揈��
	void												DrawFromGBuffer();
	//Shader�̓ǂݍ���
	bool												LoadShaders();
	//Sprite�̒��_���쐬
	void												CreateSpriteVerts();

	int 												CreateFanSpriteVerts(float fillRatio /*0.0�`1.0: ��̊���*/, int segments);
	//LineSprite�̒��_���쐬
	//���݂͖��g�p
	void												CreateLineSpriteVerts();
	//���C�g��Shader�A�}�g���b�N�X��Setter
	void												SetLightUniforms(class Shader* shader, const Matrix4& view);
	// �e�N�X�`���̃}�b�v���ǂݍ��ݕϐ�
	std::unordered_map<string, class Texture*>			mTextures;
	// ���b�V���̒n�}�����[�h
	std::unordered_map<string, class Mesh*>				mMeshes;
	// �`���ꂽ���ׂẴX�v���C�g�R���|�[�l���g
	vector<class SpriteComponent*>						mSprites;
	//���g�p
	vector<class LineRenderer*>							mLineSprites;
	// ���ׂẮi���i�ȊO�́j���b�V���R���|�[�l���g
	vector<class MeshRenderer*>							mMeshComps;
	vector<class SkeletalMeshRenderer*>					mSkeletalMeshes;
	// BaseScene
	class BaseScene*									mNowScene;
	//***Shader***
	// Sprite shader
	class Shader*										mSpriteShader;
	// Sprite vertex array
	class VertexArray*									mSpriteVerts;

	class VertexArray*									mFanSpriteVerts;

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


	class GBuffer*										mGBuffer;
	// GBuffer shader
	class Shader*										mGGlobalShader;
	class Shader*										mGPointLightShader;
	vector<class PointLightComponent*>					mPointLights;
	class Mesh*											mPointLightMesh;
	/*
	//Line Shader
	class Shader*										mLineShader;
	// Sprite vertex array
	class VertexArray*									mLineSpriteVerts;
	*/

};