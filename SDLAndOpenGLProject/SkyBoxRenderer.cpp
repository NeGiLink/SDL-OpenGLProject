#include "SkyBoxRenderer.h"

SkyBoxRenderer::SkyBoxRenderer()
    : mGame(nullptr)
    , mTexture(nullptr)
    , mCubeVAO(nullptr)
    , mVerticesCount(36)
{
    // キューブ頂点生成
	float skyboxVertices[] = {
		// positions          
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f
	};
    mCubeVAO = new VertexArray(skyboxVertices, 36, VertexArray::Pos, nullptr, 0);
}

SkyBoxRenderer::~SkyBoxRenderer()
{
    UnLoad();
}

void SkyBoxRenderer::Load(const std::string& file, int faceSize)
{
	if (mTexture)
	{
		mTexture->Unload();
		delete mTexture;
		mTexture = nullptr;
	}
    mTexture = new Texture();
	string filePath = TexFile::TextureFilePath + file;
    mTexture->LoadEquirectangularToCubemap(filePath, faceSize);
}

void SkyBoxRenderer::Draw(class Shader* shader, const Matrix4& view, const Matrix4& proj)
{
	if (!mTexture) return;

	glDepthFunc(GL_LEQUAL);
	glDepthMask(GL_FALSE);  // 深度バッファ書き込み禁止

	// カリングを一時的にオフ
	GLboolean cullEnabled = glIsEnabled(GL_CULL_FACE);
	if (cullEnabled) glDisable(GL_CULL_FACE);

	// ビュー行列から位置成分を削除
	Matrix4 viewNoTrans = view;
	viewNoTrans.mat[3][0] = 0.0f;
	viewNoTrans.mat[3][1] = 0.0f;
	viewNoTrans.mat[3][2] = 0.0f;

	shader->SetActive();
	shader->SetMatrixUniform("uView", viewNoTrans);
	shader->SetMatrixUniform("uProj", proj);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, mTexture->GetTextureID());
	shader->SetIntUniform("skybox", 0);

	mCubeVAO->SetActive();
	glDrawArrays(GL_TRIANGLES, 0, mVerticesCount);

	// 元のカリング設定を復元
	if (cullEnabled) glEnable(GL_CULL_FACE);

	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LESS);
}

void SkyBoxRenderer::UnLoad()
{
    if (mTexture) {
        mTexture->Unload();
        delete mTexture;
        mTexture = nullptr;
    }
    if (mCubeVAO) {
        delete mCubeVAO;
        mCubeVAO = nullptr;
    }
}