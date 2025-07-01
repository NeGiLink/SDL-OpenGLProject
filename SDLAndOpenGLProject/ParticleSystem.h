#pragma once
#include "Component.h"
#include "Shader.h"
#include "Actor.h"
#include "Texture.h"
#include "Random.h"

/*
* ===エンジン内部処理/Engine internal processing===
*/

//パーティクルの構造体
struct ParticleStruct
{
	Vector3 mPosition;
	Vector3 mVelocity;
	Vector4 mColor;
	float mMaxLifetime;
	float mLifetime;
	float mSize;
	bool mActive;
};

class ParticleSystem : public Component
{
protected:
	// パーティクルのインスタンス
	vector<ParticleStruct*> mParticle;

	class Texture*			mParticleTexture;

	// パーティクルのループフラグ
	bool					mIsLoop; 

	bool					mVisible;

	// 最大パーティクル数
	int						mMaxParticleCount; 

	float					mParticleLifeTime;

	Vector3					mEmitterPosition;
public:
	ParticleSystem(class ActorObject* owner);
	~ParticleSystem();

	void						Update(float deltaTime)override;

	virtual void				Draw(class Shader* shader);

	void						LoadTexture(string name);

	void						Emit(Vector3 pos, int count);

	// パーティクルを取得
	vector<ParticleStruct*>		GetParticle() const { return mParticle; }

	bool						IsVisible() const { return mVisible; }

	void						SetVisible(bool visible) { mVisible = visible; }

	bool 						IsLoop() const { return mIsLoop; }
	void						SetLoop(bool loop) { mIsLoop = loop; }
};

