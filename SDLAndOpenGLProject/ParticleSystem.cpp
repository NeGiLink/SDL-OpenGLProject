#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(ActorObject* owner)
	: Component(owner)
	, mVisible(true)
	, mIsLoop(false)
	, mParticleLifeTime(5.0f) // デフォルトのパーティクルライフタイム
	, mMaxParticleCount(10) // デフォルトの最大パーティクル数
{
	owner->GetGame()->GetWinMain()->GetRenderer()->AddParticleComp(this);

	for(int i = 0; i < mMaxParticleCount; ++i)
	{
		ParticleStruct* particle = new ParticleStruct();
		particle->mPosition = Vector3::Zero; // 初期位置
		particle->mVelocity = Vector3::Zero; // 初期速度
		particle->mColor = Vector4(1.0f, 1.0f, 1.0f, 1.0f); // 初期色（白）
		particle->mMaxLifetime = mParticleLifeTime; // 最大ライフタイム
		particle->mLifetime = mParticleLifeTime; // 初期ライフタイム
		particle->mSize = 1.0f; // 初期サイズ
		particle->mActive = true; // 初期状態は非アクティブ
		mParticle.push_back(particle);
	}

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
		mEmitterPosition = mOwner->GetPosition() + pos;
		// ランダムで生成
		mParticle[i]->mVelocity = Random::GetVector(Vector3(-1.0f, -1.0f, -1.0f), Vector3(1.0f, 1.0f, 1.0f)) * Random::GetFloatRange(0.5f, 2.0f);
		// ライフタイムをランダムに設定
		mParticle[i]->mLifetime = mParticleLifeTime;
		// 最大ライフタイムも同じ値に設定
		mParticle[i]->mMaxLifetime = mParticle[i]->mLifetime; 
	}
}

void ParticleSystem::Update(float deltaTime)
{
	for (auto p : mParticle)
	{
		if (!p->mActive) continue;
		p->mPosition += p->mVelocity * deltaTime;
		p->mLifetime -= deltaTime;
		if (p->mLifetime <= 0.0f) 
		{
			if (mIsLoop)
			{
				p->mPosition = mEmitterPosition;
				p->mLifetime = mParticleLifeTime;
			}
			else
			{
				p->mActive = false;
			}
		}
	}
}

void ParticleSystem::Draw(Shader* shader)
{
	for(int i = 0; i < mParticle.size(); ++i)
	{
		if (mParticle[i]->mActive)
		{
			ParticleStruct* particle = mParticle[i];

			// モデル行列（ビルボード化してもOK）
			Matrix4 world = Matrix4::CreateScale(particle->mSize);
			world *= Matrix4::CreateTranslation(particle->mPosition);

			shader->SetMatrixUniform("uWorldTransform", world);
			shader->SetVector4Uniform("uColor", particle->mColor);

			particle->mColor.w = particle->mLifetime / particle->mMaxLifetime; // アルファフェード

			//画像をテクスチャとして使用する場合は、ここでバインドします
			mParticleTexture->SetActive();
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		}
	}
}
