#include "Image.h"


Image::Image()
	:mGame(GameApp::GetActiveScene())
	,mTexture(nullptr)
	,mAngleZ(0)
{
	mTexScale = Vector3(1.0f, 1.0f, 1.0f);
	mFillAmount = 1.0f;
	mFillMethod = FillMethod::None;

	//BaseSceneに送る処理
	mGame->PushImage(this);
}

Image::~Image()
{
}

void Image::Load(string file)
{
	string filePath = TexFile::TextureFilePath + file;
	mTexture = mGame->GetWinMain()->GetRenderer()->GetTexture(filePath);
	mTextureRect.x = 0;
	mTextureRect.y = 0;
	mTextureRect.w = static_cast<float>(mTexture->GetWidth());
	mTextureRect.h = static_cast<float>(mTexture->GetHeight());
}

void Image::SetTexture(Texture* texture)
{
	mTexture = texture;
}

void Image::SetPosition(Vector2 pos)
{
	mTexturePos = pos;
}

void Image::SetScale(Vector3 scale)
{
	mTexScale = scale;
}

void Image::SetFillAmount(float fill)
{
	mFillAmount = Math::Clamp(fill, 0.0f, 1.0f);
}

void Image::SetAngleZ(float angle)
{
	mAngleZ = angle;
}

void Image::Update(float deltaTime)
{
}

void Image::Draw(Shader* shader)
{
	// Draw title (if exists)
	if (mTexture)
	{
		DrawTexture(shader);
	}
}

void Image::UnLoad()
{
	if (mTexture) 
	{
		mTexture->Unload();
		delete mTexture;
	}
}

void Image::Close()
{
	mState = EClosing;
}

void Image::Active()
{
	mState = EActive;
}

void Image::DrawTexture(Shader* shader)
{
	float texW = static_cast<float>(mTexture->GetWidth());
	float texH = static_cast<float>(mTexture->GetHeight());

	// UV範囲の計算
	float u1 = mTextureRect.x / texW;
	float v1 = mTextureRect.y / texH;
	float u2 = (mTextureRect.x + mTextureRect.w) / texW;
	float v2 = (mTextureRect.y + mTextureRect.h) / texH;

	// 横幅をmFillAmountでスケール
	float width = static_cast<float>(mTextureRect.w);
	float height = static_cast<float>(mTextureRect.h);

	float offsetX = 0;
	float offsetY = 0;

	Vector4 uvTransform = Vector4(0, 0, 1, 1);
	int verticesCount = 6;
	// VAO/VBO/IBO生成
	//GLuint vao, vbo, ibo;
	if (mFillMethod == FillMethod::Horizontal)
	{
		float filledU2 = u1 + (u2 - u1) * mFillAmount;
		uvTransform.x = u1;
		uvTransform.y = v1;
		uvTransform.z = filledU2 - u1;
		uvTransform.w = v2 - v1;

		// 横幅をmFillAmountでスケール
		width *= mFillAmount;

		// 左端を固定して右に伸びるように位置補正（中心基準からオフセット）
		offsetX = (1.0f - mFillAmount) * 0.5f * mTextureRect.w * mTexScale.x;
	}
	else if (mFillMethod == FillMethod::Vertical)
	{
		// UV（v1を上にずらす）
		float filledV1 = v1 + (v2 - v1) * (1.0f - mFillAmount);
		uvTransform.x = u1;
		uvTransform.y = filledV1;
		uvTransform.z = u2 - u1;
		uvTransform.w = v2 - filledV1;


		// スケーリング（高さをfillAmount倍）
		height *= mFillAmount;

		// Y方向の位置補正（下から上に伸びるので上にずらす）
		offsetY = (1.0f - mFillAmount) * 0.5f * texH;
	}
	else if (mFillMethod == FillMethod::Radial360)
	{
		verticesCount = mVerticesCount;
	}

	shader->SetVector4Uniform("uTexUV", uvTransform);

	Matrix4 scaleMat = Matrix4::CreateScale(
		width * mTexScale.x,
		height * mTexScale.y,
		mTexScale.z);


	Matrix4 transMat = Matrix4::CreateTranslation(
		Vector3(mTexturePos.x - offsetX, mTexturePos.y - offsetY, 0.0f));

	Matrix4 rotationMat = Matrix4::CreateRotationZ(mAngleZ);

	Matrix4 world = scaleMat * rotationMat * transMat;
	
	shader->SetMatrixUniform("uWorldTransform", world);

	mTexture->SetActive();
	
	glDrawElements(GL_TRIANGLES, verticesCount, GL_UNSIGNED_INT, nullptr);
}

Vector4 Image::UVCalculation()
{
	return Vector4();
}

Matrix4 Image::WorldMatrixCalculation()
{
	return Matrix4();
}
