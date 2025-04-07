#pragma once
#include "BoneTransform.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <assimp/mesh.h>

class Skeleton
{
public:
	enum SkeletonType 
	{
		Humanoid,
		Generic
	};
	// Definition for each bone in the skeleton
	struct Bone
	{
		//TODO：後の計算用にオフセットを追加
		//		※今回は親子関係構築後にmLocalBindPoseを求めるのを楽するため追加
		//		このままだとゲームのBone情報にassimpの情報を含めてしまうため変更するべき
		aiMatrix4x4 mOffsetMatrix;

		BoneTransform mLocalBindPose;
		std::string mName;
		std::string mGetName;
		int mParent;
	};

	bool Load(const std::string& fileName);

	// Load from a file
	bool LoadFromJSON(const std::string& fileName);

	bool LoadFromFBX(const std::string& fileName);

	void SetParentBones(aiNode* node, int parentIndex);

	std::string ConvertSimpleBoneName(std::string boneName);

	bool EndsWith(const std::string& str, const std::string& suffix);



	// Getter functions
	size_t GetNumBones() const { return mBones.size(); }

	const Bone& GetBone(size_t idx) const { return mBones[idx]; }
	
	const std::vector<Bone>& GetBones() const { return mBones; }
	
	const std::vector<Matrix4>& GetGlobalInvBindPoses() const { return mGlobalInvBindPoses; }
	const std::vector<Matrix4>& GetGlobalCurrentPoses() const { return mGlobalCurrentPoses; }
	void SetGlobalCurrentPoses(std::vector<Matrix4>& poses) { mGlobalCurrentPoses = poses; }
	
	const std::unordered_map<std::string, int>& GetBoneNameToIndex() const { return boneNameToIndex; }

	Matrix4 GetBonePosition(std::string boneName);
protected:
	// Called automatically when the skeleton is loaded
	// Computes the global inverse bind pose for each bone
	void ComputeGlobalInvBindPose();
private:
	// The bones in the skeleton
	std::vector<Bone> mBones;
	// The global inverse bind poses for each bone
	std::vector<Matrix4> mGlobalInvBindPoses;

	std::vector<Matrix4> mGlobalCurrentPoses;

	std::unordered_map<std::string, int> boneNameToIndex;

	std::unordered_map<std::string,int> mBoneTransform;

	SkeletonType mSkeletonType;
};