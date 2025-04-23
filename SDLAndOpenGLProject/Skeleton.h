#pragma once
#include "BoneTransform.h"
#include "BoneActor.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <assimp/mesh.h>

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
		std::string mName;
		std::string mGetName;
		int mParent;
	};

	bool Load(const std::string& fileName);

	// ファイルから読み込み
	bool LoadFromJSON(const std::string& fileName);

	bool LoadFromFBX(const std::string& fileName);

	void SetParentBones(aiNode* node, int parentIndex);

	std::string ConvertSimpleBoneName(std::string boneName);

	bool EndsWith(const std::string& str, const std::string& suffix);



	// Getter functions
	size_t GetNumBones() const { return mBones.size(); }

	const Bone& GetBone(size_t idx) const { return mBones[idx]; }
	
	const std::vector<Bone>& GetBones() const { return mBones; }

	std::vector<BoneActor*> GetBoneActor() const { return mBoneActors; }
	
	const std::vector<Matrix4>& GetGlobalInvBindPoses() const { return mGlobalInvBindPoses; }

	//アニメーション適用後のボーンの行列変数のGetter
	const std::vector<Matrix4>& GetGlobalCurrentPoses() const { return mGlobalCurrentPoses; }
	//アニメーション適用語の各ボーンの行列をセットするSetter
	void SetGlobalCurrentPoses(std::vector<Matrix4>& poses) { mGlobalCurrentPoses = poses; }
	
	const std::unordered_map<std::string, int>& GetBoneNameToIndex() const { return boneNameToIndex; }

	Matrix4 GetBonePosition(std::string boneName);
	//指定したボーンにオブジェクトを子オブジェクトとして設定
	void AddBoneChildActor(std::string boneName,class ActorObject* actor);

	void SetParentActor(ActorObject* parent);
protected:
	// スケルトンがロードされると自動的に呼び出され、
	// 各ボーンのグローバルインバインドポーズを計算。
	void ComputeGlobalInvBindPose();
private:
	// 骨格の骨
	std::vector<Bone>						mBones;
	std::vector<BoneActor*>					mBoneActors;
	//計算用のオフセット変数
	std::vector<aiMatrix4x4>				mOffsetMatrix;
	// 各Boneに対するグローバル逆束縛ポーズ
	std::vector<Matrix4>					mGlobalInvBindPoses;
	//スケルトンのボーンのアニメーション適用後の座標を持つマトリックス
	std::vector<Matrix4>					mGlobalCurrentPoses;

	std::unordered_map<std::string, int>	boneNameToIndex;

	std::unordered_map<std::string,int>		mBoneTransform;

	SkeletonType							mSkeletonType;
};