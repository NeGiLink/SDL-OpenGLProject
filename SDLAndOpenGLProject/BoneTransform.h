#pragma once
#include "Math.h"
#include "Actor.h"

//スケルタルモデルのボーンのトランスフォームクラス
class BoneTransform
{
public:
	Matrix4 ToMatrix() const;

	void FromMatrix(Matrix4& mat);

	static BoneTransform Interpolate(const BoneTransform& a, const BoneTransform& b, float f);

	// 現状はデータを公開にしています。
	//また後々整理はする予定です。
	Vector3			mScale;

	Quaternion		mRotation;
	
	Vector3			mPosition;
};