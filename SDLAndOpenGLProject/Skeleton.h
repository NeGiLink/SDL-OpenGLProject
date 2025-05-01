#pragma once
#include "BoneTransform.h"
#include "BoneActor.h"
#include "Assimp.h"
#include "MatrixPalette.h"
#include <GL/glew.h>
#include "Actor.h"


class Skeleton
{
public:
	//スケルトンのタイプのタグ
	enum SkeletonType 
	{
		Humanoid,
		Generic
	};
	// 骨格の各骨の定義
	struct Bone
	{
		BoneTransform mLocalBindPose;
		string mName;
		string mShortName;
		int mParent;
	};

	bool Load(const string& fileName);

	// ファイルから読み込み
	bool LoadFromJSON(const string& fileName);

	bool LoadFromFBX(const string& fileName);

	void SetParentBones(aiNode* node, int parentIndex);

	string ConvertSimpleBoneName(string boneName);

	bool EndsWith(const string& str, const string& suffix);

	aiVector3D GetTranslation(const aiMatrix4x4& matrix) {
		return aiVector3D(matrix.a4, matrix.b4, matrix.c4);
	}

	// Getter functions
	size_t GetNumBones() const { return mBones.size(); }

	const Bone& GetBone(size_t idx) const { return mBones[idx]; }
	
	const vector<Bone>& GetBones() const { return mBones; }

	vector<BoneActor*> GetBoneActor() const { return mBoneActors; }
	
	const vector<Matrix4>& GetGlobalInvBindPoses() const { return mGlobalInvBindPoses; }

	//アニメーション適用後のボーンの行列変数のGetter
	const vector<Matrix4>& GetGlobalCurrentPoses() const { return mGlobalCurrentPoses; }
	//アニメーション適用語の各ボーンの行列をセットするSetter
	void SetGlobalCurrentPoses(vector<Matrix4>& poses) { mGlobalCurrentPoses = poses; }
	
	const std::unordered_map<string, int>& GetBoneNameToIndex() const { return boneNameToIndex; }

	Matrix4 GetBonePosition(string boneName);
	//指定したボーンにオブジェクトを子オブジェクトとして設定
	void AddBoneChildActor(string boneName,class ActorObject* actor);

	void SetParentActor(ActorObject* parent);
protected:
	// スケルトンがロードされると自動的に呼び出され、
	// 各ボーンのグローバルインバインドポーズを計算。
	void ComputeGlobalInvBindPose();
private:
	// 骨格の骨
	vector<Bone>						mBones;
	vector<BoneActor*>					mBoneActors;
	//計算用のオフセット変数
	vector<aiMatrix4x4>				mOffsetMatrix;
	// 各Boneに対するグローバル逆束縛ポーズ
	vector<Matrix4>					mGlobalInvBindPoses;
	//スケルトンのボーンのアニメーション適用後の座標を持つマトリックス
	vector<Matrix4>					mGlobalCurrentPoses;

	std::unordered_map<string, int>	boneNameToIndex;

	std::unordered_map<string,int>		mBoneTransform;

	SkeletonType							mSkeletonType;
};