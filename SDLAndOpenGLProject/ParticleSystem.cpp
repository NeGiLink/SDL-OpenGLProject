#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(ActorObject* owner)
	: Component(owner)
	, mVisible(true)
	, mIsLoop(false)
	, mIsDestroyed(false)
	, mParticleLifeTime(1.0f) // デフォルトのパーティクルライフタイム
	, mParticleAllLifeTime(1.0f) // デフォルトの最大パーティクルライフタイム
	, mMaxParticleCount(10) // デフォルトの最大パーティクル数
	, mParticleEmitSpeed(Vector3(1.0f, 2.0f, 1.0f)) // デフォルトのパーティクル発射速度
	, mParticleColor(Vector4(1.0f, 1.0f, 1.0f, 0.5f)) // デフォルトのパーティクル色
{
	owner->GetGame()->GetWinMain()->GetRenderer()->AddParticleComp(this);

	for(int i = 0; i < mMaxParticleCount; ++i)
	{
		ParticleStruct* particle = new ParticleStruct();
		particle->mPosition = Vector3::Zero; // 初期位置
		particle->mVelocity = Vector3::Zero; // 初期速度
		mParticleColor = Vector4(1.0f, 1.0f, 1.0f, 0.5f); // 初期色（白）
		particle->mMaxLifetime = mParticleLifeTime; // 最大ライフタイム
		particle->mLifetime = mParticleLifeTime; // 初期ライフタイム
		particle->mSize = 1.0f; // 初期サイズ
		particle->mActive = true; // 初期状態は非アクティブ
		mParticle.push_back(particle);
	}
	mParticleAllLifeTime = mParticleLifeTime;

	//生成時に初期画像を読み込む
	mParticleTexture = GetOwner()->GetGame()->GetWinMain()->GetRenderer()->GetTexture("Assets/Particle/Default.png");
}

ParticleSystem::~ParticleSystem()
{
	GetOwner()->GetGame()->GetWinMain()->GetRenderer()->RemoveParticleComp(this);
}

void ParticleSystem::LoadTexture(string name)
{
	string path = Model::AssetPath + "Particle/" + name;
	mParticleTexture = GetOwner()->GetGame()->GetWinMain()->GetRenderer()->GetTexture(path);
	if (!mParticleTexture)
	{
		SDL_Log("Failed to load particle texture: %s", path.c_str());
		return;
	}
}

void ParticleSystem::Emit(Vector3 pos, int count)
{
	for (int i = 0; i < mParticle.size(); ++i) 
	{
		mParticle[i]->mActive = true;
		mParticle[i]->mPosition = mOwner->GetPosition() + pos;
		// ランダムで生成
		mParticle[i]->mVelocity = Random::GetVector(Vector3(-1.0f, 0.0f, -1.0f), Vector3(1.0f, 1.0f, 1.0f)) * Random::GetFloatRange(0.5f, 2.0f);
		// ライフタイムをランダムに設定
		mParticle[i]->mLifetime = mParticleLifeTime;
		// 最大ライフタイムも同じ値に設定
		mParticle[i]->mMaxLifetime = mParticle[i]->mLifetime; 
	}
	mParticleAllLifeTime = mParticleLifeTime;
}

void ParticleSystem::ResetEmitOne(ParticleStruct* particle)
{
	particle->mActive = true;
	particle->mPosition = mOwner->GetPosition();
	// ランダムで生成
	particle->mVelocity = Random::GetVector(Vector3(-1.0f, 0.0f, -1.0f), Vector3(1.0f, 1.0f, 1.0f)) * Random::GetFloatRange(0.5f, 2.0f);
	// ライフタイムをランダムに設定
	particle->mLifetime = mParticleLifeTime;
	// 最大ライフタイムも同じ値に設定
	particle->mMaxLifetime = particle->mLifetime;
}

void ParticleSystem::SetParticleSpeed(Vector3 speed)
{
	mParticleEmitSpeed = speed;
}

void ParticleSystem::SetColor(Vector4 color)
{
	mParticleColor = color;
}

void ParticleSystem::Update(float deltaTime)
{
	mParticleAllLifeTime -= deltaTime;
	// パーティクルのライフタイムを更新
	for (auto p : mParticle)
	{
		if (!p->mActive) continue;
		p->mPosition += (p->mVelocity * mParticleEmitSpeed) * deltaTime;
		p->mLifetime -= deltaTime;
		if (p->mLifetime <= 0.0f) 
		{
			if (mIsLoop)
			{
				ResetEmitOne(p);
			}
			else
			{
				p->mActive = false;
			}
		}
	}
	if( mParticleAllLifeTime <= 0.0f)
	{
		if(mIsDestroyed)
		{
			mOwner->SetState(ActorObject::EDead);
		}
		else
		{
			mParticleAllLifeTime = mParticleLifeTime;
		}
	}
}

void ParticleSystem::Draw(Shader* shader)
{
	// カメラのビュー行列の逆行列を取得（ワールド変換行列）
	Matrix4 viewMatrix = GetOwner()->GetGame()->GetWinMain()->GetRenderer()->GetView();
	viewMatrix.Invert(); // カメラのワールド空間情報

	// カメラの向きを取得
	Vector3 camRight = viewMatrix.GetXAxis(); // X方向（右）
	Vector3 camUp = viewMatrix.GetYAxis(); // Y方向（上）
	Vector3 camForward = viewMatrix.GetZAxis(); // Z方向（前）
	for(int i = 0; i < mParticle.size(); ++i)
	{
		if (mParticle[i]->mActive)
		{
			ParticleStruct* p = mParticle[i];

			// モデル行列
			// === ビルボード用ワールド行列を作成 ===
			Matrix4 world = Matrix4::Billboard(
				p->mPosition, 
				p->mSize, 
				camRight, 
				camUp, 
				camForward
			);

			shader->SetMatrixUniform("uWorldTransform", world);
			shader->SetVector4Uniform("uColor", mParticleColor);

			//アルファフェード
			//particle->mColor.w = particle->mLifetime / particle->mMaxLifetime; 

			//画像をテクスチャとして使用する場合は、ここでバインドします
			mParticleTexture->SetActive();
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		}
	}
}
