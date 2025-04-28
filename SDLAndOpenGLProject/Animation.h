#pragma once
#include "BoneTransform.h"
#include "Assimp.h"
#include "SDL3.h"

//アニメーション1つの情報を持つクラス
class Animation
{
public:
	Animation(class Skeleton* skeleton);

	bool Load(const std::string& fileName);

	size_t	GetNumBones() const { return mNumBones; }
	
	size_t	GetNumFrames() const { return mNumFrames; }
	
	float	GetDuration() const { return mDuration; }
	
	float	GetFrameDuration() const { return mFrameDuration; }

	void	SetSkeleton(class Skeleton* skeleton) { mSkeleton = skeleton; }

	bool	IsLoop() const { return isLoop; }

	void	SetLoop(bool loop) { isLoop = loop; }

	bool	IsAnimationEnd() const { return isAnimationEnd; }

	void	SetIsAnimationEnd(bool animationEnd) { isAnimationEnd = animationEnd; }

	// 指定されたアニメーションの時間における各ボーンのグローバル（現在の）ポーズ行列を提供されたベクターに充填。
	// 時間は0.0f以上でmDuration以下であること。
	void GetGlobalPoseAtTime(std::vector<Matrix4>& outPoses, const class Skeleton* inSkeleton, float inTime) const;

private:
	bool LoadFromJSON(const std::string& fileName);

	bool LoadFromFBX(const std::string& fileName);

	size_t FindTranslation(float AnimationTime, const aiNodeAnim* pNodeAnim);

	void CalcInterpolatedTranslation(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim);

	size_t FindRotation(float AnimationTime, const aiNodeAnim* pNodeAnim);

	void CalcInterpolatedRotation(aiQuaternion& Out, float AnimationTime, const aiNodeAnim* pNodeAnim);

	size_t FindScaling(float AnimationTime, const aiNodeAnim* pNodeAnim);

	void CalcInterpolatedScaling(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim);
	// アニメーションのための骨の数
	size_t									mNumBones;
	// アニメーションのフレーム数
	size_t									mNumFrames;
	// アニメーションの持続時間（秒）
	float									mDuration;
	// アニメーションにおける各フレームの持続時間
	float									mFrameDuration;
	// トラック上の各フレームに対する情報を変換。
	// 外側のベクトルの各インデックスは骨であり、
	// 内側のベクトルはフレームです。
	std::vector<std::vector<BoneTransform>> mTracks;

	class Skeleton*							mSkeleton;
	//アニメーションをループさせるためのフラグ
	bool									isLoop;
	//アニメーションが再生終了したかどうか
	bool									isAnimationEnd;
};