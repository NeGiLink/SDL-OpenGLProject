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
	float	mMaxLifetime;
	float	mLifetime;
	float	mSize;
	bool	mActive;
};
// パーティクルシステムクラス
class ParticleSystem : public Component
{
protected:
	// パーティクルのインスタンス
	vector<ParticleStruct*> mParticle;
	// パーティクルのテクスチャ
	class Texture*			mParticleTexture;
	// パーティクルのループフラグ
	bool					mIsLoop; 
	// パーティクルの可視性フラグ
	bool					mVisible;
	// パーティクルの破棄フラグ
	bool					mIsDestroyed;
	// 最大パーティクル数
	int						mMaxParticleCount; 
	// パーティクルのライフタイム
	float					mParticleLifeTime;
	// パーティクルの全体ライフタイム
	float					mParticleAllLifeTime;
	// パーティクルの発射速度
	Vector3					mParticleEmitSpeed;
	// パーティクルの色
	Vector4					mParticleColor;
public:
	ParticleSystem(class ActorObject* owner);
	~ParticleSystem();
	// パーティクルシステムの更新
	void						Update(float deltaTime)override;
	// パーティクルの描画
	virtual void				Draw(class Shader* shader);
	// テクスチャの読み込み
	void						LoadTexture(string name);
	// パーティクルの発射
	void						Emit(Vector3 pos, int count);
	// パーティクルのリセット
	void						ResetEmitOne(ParticleStruct* particle);
	// パーティクルを取得
	vector<ParticleStruct*>		GetParticle() const { return mParticle; }
	//パーティクルの可視性の取得
	bool						IsVisible() const { return mVisible; }
	// 可視性の設定
	void						SetVisible(bool visible) { mVisible = visible; }
	// ループフラグの取得
	bool 						IsLoop() const { return mIsLoop; }
	// ループフラグの設定
	void						SetLoop(bool loop) { mIsLoop = loop; }
	// 破棄フラグの取得
	bool 						IsDestroyed() const { return mIsDestroyed; }
	// 破棄フラグの設定
	void						SetDestroyed(bool destroyed) { mIsDestroyed = destroyed; }
	// 最大パーティクル数の取得
	void						SetParticleSpeed(Vector3 speed);
	// パーティクルの速度設定
	void						SetColor(Vector4 color);
	// パーティクルの色設定
	void						SetParticleLifeTime(float lifeTime) { mParticleLifeTime = lifeTime; }
};

