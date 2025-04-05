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

	bool endsWith(const std::string& str, const std::string& suffix);

	// Getter functions
	size_t GetNumBones() const { return mBones.size(); }
	const Bone& GetBone(size_t idx) const { return mBones[idx]; }
	const std::vector<Bone>& GetBones() const { return mBones; }
	const std::vector<Matrix4>& GetGlobalInvBindPoses() const { return mGlobalInvBindPoses; }
	const std::unordered_map<std::string, int>& GetBoneNameToIndex() const { return boneNameToIndex; }
	Bone* GetBone(std::string boneName);
protected:
	// Called automatically when the skeleton is loaded
	// Computes the global inverse bind pose for each bone
	void ComputeGlobalInvBindPose();
private:
	// The bones in the skeleton
	std::vector<Bone> mBones;
	// The global inverse bind poses for each bone
	std::vector<Matrix4> mGlobalInvBindPoses;

	std::unordered_map<std::string, int> boneNameToIndex;

	std::unordered_map<std::string,Bone> mBoneTransform;

	SkeletonType mSkeletonType;
};