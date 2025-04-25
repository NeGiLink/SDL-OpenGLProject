#include "Renderer.h"
#include "Texture.h"
#include "Mesh.h"
#include "Shader.h"
#include "VertexArray.h"
#include "SpriteComponent.h"
#include "LineRenderer.h"
#include "MeshRenderer.h"
#include "UIScreen.h"
#include "Image.h"
#include "WinMain.h"
#include "BaseScene.h"
#include "GameApp.h"
#include <GL/glew.h>
#include "SkeletalMeshRenderer.h"
#include "GBuffer.h"
#include "PointLightComponent.h"
#include "MeshFilePath.h"

Renderer::Renderer(GameWinMain* game)
	:mGame(game)
	, mNowScene(nullptr)
	, mSpriteShader(nullptr)
	, mMeshShader(nullptr)
	, mSkinnedShader(nullptr)
	, mMirrorBuffer(0)
	, mMirrorTexture(nullptr)
	, mGBuffer(nullptr)
	, mGGlobalShader(nullptr)
	, mGPointLightShader(nullptr)
	//,mLineShader(nullptr)
{
}

Renderer::~Renderer()
{
}

bool Renderer::Initialize(float screenWidth, float screenHeight)
{
	mScreenWidth = screenWidth;
	mScreenHeight = screenHeight;

	// OpenGL�̑�����ݒ肷��
	// �R�AOpenGL�v���t�@�C�����g�p
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	// �o�[�W����3.3���w��
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	// RGBA�`���l�����Ƃ�8�r�b�g�̃J���[�o�b�t�@�����N�G�X�g
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	// �_�u���o�b�t�@�����O��L���ɂ���
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	// OpenGL�Ƀn�[�h�E�F�A�A�N�Z�����[�V�������g�p
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

	mWindow = SDL_CreateWindow("SDL&OpenGLProject",
		static_cast<int>(mScreenWidth), static_cast<int>(mScreenHeight), SDL_WINDOW_OPENGL);
	if (!mWindow)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}

	// OpenGL�R���e�L�X�g���쐬����
	mContext = SDL_GL_CreateContext(mWindow);

	// GLEW������������
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		SDL_Log("Failed to initialize GLEW.");
		return false;
	}

	// �ꕔ�̃v���b�g�t�H�[���ł́AGLEW�����Q�ȃG���[�R�[�h���o�͂���̂ŁA
	// ������N���A�B
	glGetError();

	// �V�F�[�_�[���쐬/�R���p�C���ł��邱�Ƃ��m�F���Ă�������
	if (!LoadShaders())
	{
		SDL_Log("Failed to load shaders.");
		return false;
	}

	// �X�v���C�g��`�悷�邽�߂̎l�p�`���쐬����
	CreateSpriteVerts();

	//����`�悷�邽�߂̓�_���쐬
	//CreateLineSpriteVerts();

	// �~���[�p�̃����_�[�^�[�Q�b�g���쐬����
	if (!CreateMirrorTarget())
	{
		SDL_Log("Failed to create render target for mirror.");
		return false;
	}

	// G�o�b�t�@���쐬����
	mGBuffer = new GBuffer();
	int width = static_cast<int>(mScreenWidth);
	int height = static_cast<int>(mScreenHeight);
	if (!mGBuffer->Create(width, height))
	{
		SDL_Log("Failed to create G-buffer.");
		return false;
	}

	// �|�C���g���C�g���b�V�������[�h����
	//mPointLightMesh = GetMesh("PointLight.gpmesh");

	return true;
}

void Renderer::Shutdown()
{
	// ���݂���ꍇ�́A�����_�[�^�[�Q�b�g�e�N�X�`�������ׂč폜�B
	if (mMirrorTexture != nullptr)
	{
		glDeleteFramebuffers(1, &mMirrorBuffer);
		mMirrorTexture->Unload();
		delete mMirrorTexture;
	}
	// G�o�b�t�@����菜��
	if (mGBuffer != nullptr)
	{
		mGBuffer->Destroy();
		delete mGBuffer;
	}
	// �|�C���g���C�g���폜����
	while (!mPointLights.empty())
	{
		delete mPointLights.back();
	}
	
	delete mSpriteVerts;
	
	mSpriteShader->Unload();
	
	delete mSpriteShader;
	
	mMeshShader->Unload();
	
	delete mMeshShader;
	
	SDL_GL_DestroyContext(mContext);

	SDL_DestroyWindow(mWindow);
}

void Renderer::UnloadData()
{
	// �e�N�X�`����j�󂷂�
	for (auto i : mTextures)
	{
		i.second->Unload();
		delete i.second;
	}
	mTextures.clear();

	// ���b�V����j�󂷂�
	for (auto i : mMeshes)
	{
		i.second->Unload();
		delete i.second;
	}
	mMeshes.clear();
}

void Renderer::Draw()
{
	// �܂����̃e�N�X�`����`�悵�܂��B
	// Draw3DScene(mMirrorBuffer, mMirrorView, mProjection, 0.25f);
	// G-buffer��3D�V�[����`�悵�܂��B
	Draw3DScene(mGBuffer->GetBufferID(), mView, mProjection, 1.0f, false);
	// �t���[���o�b�t�@���[���i�X�N���[���̃t���[���o�b�t�@�j�ɖ߂��܂�
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	// G�o�b�t�@����`�悷��
	DrawFromGBuffer();

	// ���ׂẴX�v���C�g�R���|�[�l���g��`�悷��
	// �[�x�o�b�t�@�����O�𖳌��ɂ���
	glDisable(GL_DEPTH_TEST);
	// �J���[ �o�b�t�@�ŃA���t�@ �u�����f�B���O��L���ɂ��܂�
	glEnable(GL_BLEND);
	glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);

	// �V�F�[�_�[/VAO���A�N�e�B�u�ɐݒ�
	mSpriteShader->SetActive();
	mSpriteVerts->SetActive();

	for (auto sprite : mSprites)
	{
		if (sprite->GetVisible())
		{
			sprite->Draw(mSpriteShader);
		}
	}

	// Draw any UI screens
	//�Q�[������UI���܂Ƃ߂ĕ`��
	for (auto ui : mNowScene->GetUIStack())
	{
		ui->Draw(mSpriteShader);
	}

	for (auto ui : mNowScene->GetImageStack())
	{
		if (ui->GetState() == Image::EActive) 
		{
			ui->Draw(mSpriteShader);
		}
	}

	// �o�b�t�@�����ւ���
	SDL_GL_SwapWindow(mWindow);
}

void Renderer::AddSprite(SpriteComponent* sprite)
{
	//�\�[�g���ꂽ�x�N�^�[���̑}���|�C���g��������
	// �i���݂��������`�揇�������ŏ��̗v�f�j
	int myDrawOrder = sprite->GetDrawOrder();
	auto iter = mSprites.begin();
	for (;
		iter != mSprites.end();
		++iter)
	{
		if (myDrawOrder < (*iter)->GetDrawOrder())
		{
			break;
		}
	}

	// �C�e���[�^�̈ʒu�̑O�ɗv�f��}�����܂�
	mSprites.insert(iter, sprite);
}

void Renderer::RemoveSprite(SpriteComponent* sprite)
{
	auto iter = std::find(mSprites.begin(), mSprites.end(), sprite);
	mSprites.erase(iter);
}

void Renderer::AddLineSprite(LineRenderer* sprite)
{
	//�\�[�g���ꂽ�x�N�^�[���̑}���|�C���g��������
// �i���݂��������`�揇�������ŏ��̗v�f�j
	int myDrawOrder = sprite->GetDrawOrder();
	auto iter = mLineSprites.begin();
	for (;
		iter != mLineSprites.end();
		++iter)
	{
		if (myDrawOrder < (*iter)->GetDrawOrder())
		{
			break;
		}
	}

	// �C�e���[�^�̈ʒu�̑O�ɗv�f��}�����܂�
	mLineSprites.insert(iter, sprite);
}

void Renderer::RemoveLineSprite(LineRenderer* sprite)
{
	auto iter = std::find(mLineSprites.begin(), mLineSprites.end(), sprite);
	mLineSprites.erase(iter);
}

void Renderer::AddMeshComp(MeshRenderer* mesh)
{
	if (mesh->GetIsSkeletal())
	{
		SkeletalMeshRenderer* sk = static_cast<SkeletalMeshRenderer*>(mesh);
		mSkeletalMeshes.emplace_back(sk);
	}
	else
	{
		mMeshComps.emplace_back(mesh);
	}
}

void Renderer::RemoveMeshComp(MeshRenderer* mesh)
{
	if (mesh->GetIsSkeletal())
	{
		SkeletalMeshRenderer* sk = static_cast<SkeletalMeshRenderer*>(mesh);
		auto iter = std::find(mSkeletalMeshes.begin(), mSkeletalMeshes.end(), sk);
		mSkeletalMeshes.erase(iter);
	}
	else
	{
		auto iter = std::find(mMeshComps.begin(), mMeshComps.end(), mesh);
		mMeshComps.erase(iter);
	}
}

void Renderer::AddPointLight(PointLightComponent* light)
{
	mPointLights.emplace_back(light);
}

void Renderer::RemovePointLight(PointLightComponent* light)
{
	auto iter = std::find(mPointLights.begin(), mPointLights.end(), light);
	mPointLights.erase(iter);
}

Texture* Renderer::GetTexture(const std::string& fileName)
{
	Texture* tex = nullptr;
	auto iter = mTextures.find(fileName);
	if (iter != mTextures.end())
	{
		tex = iter->second;
	}
	else
	{
		tex = new Texture();
		if (tex->Load(fileName))
		{
			mTextures.emplace(fileName, tex);
		}
		else
		{
			delete tex;
			tex = nullptr;
		}
	}
	return tex;
}

Mesh* Renderer::GetMesh(const std::string& fileName)
{
	std::string file = Model::ModelPath + fileName;
	Mesh* m = nullptr;
	auto iter = mMeshes.find(file);
	if (iter != mMeshes.end())
	{
		m = iter->second;
	}
	else
	{
		m = new Mesh();
		if (m->Load(file, this , 0))
		{
			mMeshes.emplace(file, m);
		}
		else
		{
			delete m;
			m = nullptr;
		}
	}
	return m;
}

std::vector<class Mesh*> Renderer::GetMeshs(const std::string& fileName)
{
	std::string file = Model::ModelPath + fileName;
	//�Ԃ������̃��b�V��
	std::vector<class Mesh*> ms;
	//���b�V���̐����m�F����p
	Mesh* m = nullptr;
	m = new Mesh();
	int maxMesh = m->CheckMeshIndex(file, this);
	for (int i = 0; i < maxMesh; i++)
	{
		std::string inTex = std::to_string(i);
		Mesh* mesh = nullptr;
		auto iter = mMeshes.find(file + inTex.c_str());
		if (iter != mMeshes.end())
		{
			mesh = iter->second;
		}
		else
		{
			mesh = new Mesh();
			if (mesh->Load(file, this , i))
			{
				mMeshes.emplace(file + inTex.c_str(), mesh);
			}
			else
			{
				delete mesh;
				mesh = nullptr;
			}
		}

		if (mesh != nullptr) {
			ms.push_back(mesh);
		}
	}
	return ms;
}

void Renderer::Draw3DScene(unsigned int framebuffer, const Matrix4& view, const Matrix4& proj,
	float viewPortScale, bool lit)
{
	// ���݂̃t���[���o�b�t�@��ݒ肷��
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

	// �X�P�[���Ɋ�Â��ăr���[�|�[�g�T�C�Y��ݒ肵�܂�
	glViewport(0, 0,
		static_cast<int>(mScreenWidth * viewPortScale),
		static_cast<int>(mScreenHeight * viewPortScale)
	);

	// �J���[ �o�b�t�@/�[�x�o�b�t�@���N���A
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glDepthMask(GL_TRUE);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// ���b�V���R���|�[�l���g��`�悷��[�x�o�b�t�@�����O��L���ɂ���
	// �A���t�@�u�����h�𖳌��ɂ���
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	// ���b�V���V�F�[�_�[���A�N�e�B�u�ɐݒ肵�܂�
	mMeshShader->SetActive();
	// �r���[���e�s����X�V����
	mMeshShader->SetMatrixUniform("uViewProj", view * proj);
	// �Ɩ��̃��j�t�H�[�����X�V����
	if (lit)
	{
		SetLightUniforms(mMeshShader, view);
	}

	for (auto mc : mMeshComps)
	{
		if (mc->GetVisible())
		{
			mc->Draw(mMeshShader);
		}
	}

	// �X�L�����b�V����L��
	mSkinnedShader->SetActive();
	// �r���[���e�s����X�V����
	mSkinnedShader->SetMatrixUniform("uViewProj", view * proj);
	// �Ɩ��̃��j�t�H�[�����X�V����
	if (lit)
	{
		SetLightUniforms(mSkinnedShader, view);
	}
	for (auto sk : mSkeletalMeshes)
	{
		if (sk->GetVisible())
		{
			sk->Draw(mSkinnedShader);
		}
	}
}

bool Renderer::CreateMirrorTarget()
{
	int width = static_cast<int>(mScreenWidth) / 4;
	int height = static_cast<int>(mScreenHeight) / 4;

	// �~���[�e�N�X�`���̃t���[���o�b�t�@�𐶐�����
	glGenFramebuffers(1, &mMirrorBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, mMirrorBuffer);

	// �����_�����O�Ɏg�p����e�N�X�`�����쐬���܂�
	mMirrorTexture = new Texture();
	mMirrorTexture->CreateForRendering(width, height, GL_RGB);

	// ���̃^�[�Q�b�g�ɐ[�x�o�b�t�@��ǉ����Ă�������
	GLuint depthBuffer;
	glGenRenderbuffers(1, &depthBuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer);

	// �t���[���o�b�t�@�̏o�̓^�[�Q�b�g�Ƃ��ă~���[�e�N�X�`����t������
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, mMirrorTexture->GetTextureID(), 0);

	// ���̃t���[���o�b�t�@�ɕ`�悷�邽�߂̃o�b�t�@�̃��X�g��ݒ肵�܂�
	GLenum drawBuffers[] = { GL_COLOR_ATTACHMENT0 };
	glDrawBuffers(1, drawBuffers);

	// ���ׂĂ�����ɓ��삵�����Ƃ��m�F
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		// ���܂������Ȃ������ꍇ�́A�t���[���o�b�t�@���폜���A
		// �e�N�X�`�����A�����[�h/�폜���ċU��Ԃ��܂��B
		glDeleteFramebuffers(1, &mMirrorBuffer);
		mMirrorTexture->Unload();
		delete mMirrorTexture;
		mMirrorTexture = nullptr;
		return false;
	}
	return true;
}

void Renderer::DrawFromGBuffer()
{
	// �O���[�o�����C�e�B���O�p�X�̐[�x�e�X�g�𖳌��ɂ��܂�
	glDisable(GL_DEPTH_TEST);
	// �O���[�o��G�o�b�t�@�V�F�[�_���A�N�e�B�u�ɂ���
	mGGlobalShader->SetActive();
	// �X�v���C�g�̒��_�N�A�b�h��L��������
	mSpriteVerts->SetActive();
	// G�o�b�t�@�[�e�N�X�`�����T���v�����O����悤�ɐݒ肷��
	mGBuffer->SetTexturesActive();
	// �Ɩ����j�t�H�[����ݒ肷��
	SetLightUniforms(mGGlobalShader, mView);
	// �O�p�`��`��
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

	// G�o�b�t�@����f�t�H���g�t���[���o�b�t�@�ɐ[�x�o�b�t�@���R�s�[����
	glBindFramebuffer(GL_READ_FRAMEBUFFER, mGBuffer->GetBufferID());
	int width = static_cast<int>(mScreenWidth);
	int height = static_cast<int>(mScreenHeight);
	glBlitFramebuffer(0, 0, width, height,
		0, 0, width, height,
		GL_DEPTH_BUFFER_BIT, GL_NEAREST);

	// �[�x�e�X�g��L���ɂ��܂����A�[�x�o�b�t�@�ւ̏������݂𖳌��ɂ��܂��B
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_FALSE);

	// �_�����V�F�[�_�[�ƃ��b�V�����A�N�e�B�u�ɐݒ肵�܂��B
	mGPointLightShader->SetActive();
	for (unsigned int i = 0; i < mPointLightMesh->GetVertexArrays().size(); i++) {
		mPointLightMesh->GetVertexArrays()[i]->SetActive();
	}
	// �r���[���e�s���ݒ肷��
	mGPointLightShader->SetMatrixUniform("uViewProj",
		mView * mProjection);
	// �T���v�����O�̂��߂�G�o�b�t�@�[�̃e�N�X�`����ݒ肵�܂�
	mGBuffer->SetTexturesActive();

	// �_�����̐F�͊����̐F�ɒǉ������
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);

	// �|�C���g���C�g��`��
	for (PointLightComponent* p : mPointLights)
	{
		p->Draw(mGPointLightShader, mPointLightMesh);
	}
}

bool Renderer::LoadShaders()
{
	// �X�v���C�g�V�F�[�_�[���쐬����
	mSpriteShader = new Shader();
	if (!mSpriteShader->Load("Shaders/Sprite.vert", "Shaders/Sprite.frag"))
	{
		return false;
	}

	mSpriteShader->SetActive();
	// �r���[���e�s���ݒ肷��
	Matrix4 spriteViewProj = Matrix4::CreateSimpleViewProj(mScreenWidth, mScreenHeight);
	mSpriteShader->SetMatrixUniform("uViewProj", spriteViewProj);
	/*
	//Line�̕`��p�̃V�F�[�_�[���쐬����
	mLineShader = new Shader();
	if (!mLineShader->Load("Shaders/LineSprite.vert", "Shaders/LineSprite.frag")) {
		return false;
	}
	mLineShader->SetActive();
	mLineShader->SetMatrixUniform("uViewProj", spriteViewProj);
	*/

	// ��{�I�ȃ��b�V���V�F�[�_�[���쐬����
	mMeshShader = new Shader();
	if (!mMeshShader->Load("Shaders/Phong.vert", "Shaders/GBufferWrite.frag"))
	{
		return false;
	}

	mMeshShader->SetActive();
	// �r���[���e�s���ݒ肷��
	mView = Matrix4::CreateLookAt(Vector3::Zero, Vector3::UnitX, Vector3::UnitZ);
	mProjection = Matrix4::CreatePerspectiveFOV(Math::ToRadians(70.0f),
		mScreenWidth, mScreenHeight, 1.0f, 10000.0f);
	mMeshShader->SetMatrixUniform("uViewProj", mView * mProjection);

	// �X�L���V�F�[�_�[���쐬����
	mSkinnedShader = new Shader();
	if (!mSkinnedShader->Load("Shaders/Skinned.vert", "Shaders/GBufferWrite.frag"))
	{
		return false;
	}

	mSkinnedShader->SetActive();
	mSkinnedShader->SetMatrixUniform("uViewProj", mView * mProjection);

	// GBuffer����`�悷�邽�߂̃V�F�[�_�[���쐬����i�O���[�o�����C�e�B���O�j
	mGGlobalShader = new Shader();
	if (!mGGlobalShader->Load("Shaders/GBufferGlobal.vert", "Shaders/GBufferGlobal.frag"))
	{
		return false;
	}
	// GBuffer�̂��߂ɁA�e�T���v���[���C���f�b�N�X�Ɋ֘A�t����
	mGGlobalShader->SetActive();
	mGGlobalShader->SetIntUniform("uGDiffuse", 0);
	mGGlobalShader->SetIntUniform("uGNormal", 1);
	mGGlobalShader->SetIntUniform("uGWorldPos", 2);
	// �r���[���e�͂����̃X�v���C�g�̂��̂ł�
	mGGlobalShader->SetMatrixUniform("uViewProj", spriteViewProj);
	// ���E�̕ό`�X�P�[������ʂɓK�p����Ay�����]���܂�
	Matrix4 gbufferWorld = Matrix4::CreateScale(mScreenWidth, -mScreenHeight,
		1.0f);
	mGGlobalShader->SetMatrixUniform("uWorldTransform", gbufferWorld);

	// GBuffer����|�C���g���C�g�p�̃V�F�[�_�[���쐬����
	mGPointLightShader = new Shader();
	if (!mGPointLightShader->Load("Shaders/BasicMesh.vert",
		"Shaders/GBufferPointLight.frag"))
	{
		return false;
	}
	// �T���v���[�C���f�b�N�X��ݒ肷��
	mGPointLightShader->SetActive();
	mGPointLightShader->SetIntUniform("uGDiffuse", 0);
	mGPointLightShader->SetIntUniform("uGNormal", 1);
	mGPointLightShader->SetIntUniform("uGWorldPos", 2);
	mGPointLightShader->SetVector2Uniform("uScreenDimensions",
		Vector2(mScreenWidth, mScreenHeight));

	return true;
}

void Renderer::CreateSpriteVerts()
{
	float vertices[] = {
		-0.5f, 0.5f, 0.f, 0.f, 0.f, 0.0f, 0.f, 0.f, // top left
		0.5f, 0.5f, 0.f, 0.f, 0.f, 0.0f, 1.f, 0.f, // top right
		0.5f,-0.5f, 0.f, 0.f, 0.f, 0.0f, 1.f, 1.f, // bottom right
		-0.5f,-0.5f, 0.f, 0.f, 0.f, 0.0f, 0.f, 1.f  // bottom left
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	mSpriteVerts = new VertexArray(vertices, 4, VertexArray::PosNormTex, indices, 6);
}

void Renderer::CreateLineSpriteVerts()
{
	float lineVertices[] = {
	0.0f, 0.0f, 0.0f,  // �n�_ (x, y, z)
	1.0f, 1.0f, 1.0f   // �I�_ (x, y, z)
	};

	//mLineSpriteVerts = new VertexArray(lineVertices, 2);
}

void Renderer::SetLightUniforms(Shader* shader, const Matrix4& view)
{
	// �J�����̈ʒu�͋t���܂̎��_����ł�
	Matrix4 invView = view;
	invView.Invert();
	shader->SetVectorUniform("uCameraPos", invView.GetTranslation());
	// Ambient light
	shader->SetVectorUniform("uAmbientLight", mAmbientLight);
	// Directional light
	shader->SetVectorUniform("uDirLight.mDirection",
		mDirLight.mDirection);
	shader->SetVectorUniform("uDirLight.mDiffuseColor",
		mDirLight.mDiffuseColor);
	shader->SetVectorUniform("uDirLight.mSpecColor",
		mDirLight.mSpecColor);
}

Vector3 Renderer::Unproject(const Vector3& screenPoint) const
{
	// screenPoint���f�o�C�X���W�i-1����+1�̊ԁj�ɕϊ�����
	Vector3 deviceCoord = screenPoint;
	deviceCoord.x /= (mScreenWidth) * 0.5f;
	deviceCoord.y /= (mScreenHeight) * 0.5f;

	// �����e�s��Ńx�N�g����ϊ�����
	Matrix4 unprojection = mView * mProjection;
	unprojection.Invert();
	return Vector3::TransformWithPerspDiv(deviceCoord, unprojection);
}

void Renderer::GetScreenDirection(Vector3& outStart, Vector3& outDir) const
{
	// �X�^�[�g�|�C���g���擾����i�߂��̕��ʂ̉�ʂ̒��S�j
	Vector3 screenPoint(0.0f, 0.0f, 0.0f);
	outStart = Unproject(screenPoint);
	// ��ʂ̒����A�߂��Ɖ����̊ԂɃG���h�|�C���g���擾���܂��B
	screenPoint.z = 0.9f;
	Vector3 end = Unproject(screenPoint);
	// �����x�N�g�����擾����
	outDir = end - outStart;
	outDir.Normalize();
}