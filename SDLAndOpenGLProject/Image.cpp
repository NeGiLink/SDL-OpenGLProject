#include "Image.h"


Image::Image(bool active)
	:mGame(GameApp::GetActiveScene())
	,mTexture(nullptr)
	,mAngleZ(0)
{
	updateTogether = active;
	mTexScale = Vector3(1.0f, 1.0f, 1.0f);
	mFillAmount = 1.0f;


	if (updateTogether) 
	{
		//BaseSceneに送る処理
		mGame->PushImage(this);
	}
}

Image::~Image()
{
}

void Image::Load(string file)
{
	mTexture = mGame->GetWinMain()->GetRenderer()->GetTexture(file);
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

	float filledU2 = u1 + (u2 - u1) * mFillAmount;
	Vector4 uvTransform = Vector4(0, 0, 1, 1);
	uvTransform.x = u1;
	uvTransform.y = v1;
	uvTransform.z = filledU2 - u1;
	uvTransform.w = v2 - v1;
	shader->SetVector4Uniform("uTexUV", uvTransform);

	// 横幅をmFillAmountでスケール
	float width = static_cast<float>(mTextureRect.w) * mFillAmount;
	float height = static_cast<float>(mTextureRect.h);

	Matrix4 scaleMat = Matrix4::CreateScale(
		width * mTexScale.x,
		height * mTexScale.y,
		mTexScale.z);

	// 左端を固定して右に伸びるように位置補正（中心基準からオフセット）
	float offsetX = (1.0f - mFillAmount) * 0.5f * mTextureRect.w * mTexScale.x;
	Matrix4 transMat = Matrix4::CreateTranslation(
		Vector3(mTexturePos.x - offsetX, mTexturePos.y, 0.0f));

	Matrix4 rotationMat = Matrix4::CreateRotationZ(mAngleZ);
	Matrix4 world = scaleMat * rotationMat * transMat;
	shader->SetMatrixUniform("uWorldTransform", world);

	mTexture->SetActive();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}
