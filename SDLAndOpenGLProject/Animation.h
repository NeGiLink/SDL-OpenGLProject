#pragma once
#include "BoneTransform.h"
#include <vector>
#include <string>
#include <algorithm>

class Animation
{
public:
	Animation(class Skeleton* skeleton);

	bool Load(const std::string& fileName);

	size_t GetNumBones() const { return mNumBones; }
	size_t GetNumFrames() const { return mNumFrames; }
	float GetDuration() const { return mDuration; }
	float GetFrameDuration() const { return mFrameDuration; }

	// Fills the provided vector with the global (current) pose matrices for each
	// bone at the specified time in the animation. It is expected that the time
	// is >= 0.0f and <= mDuration
	void GetGlobalPoseAtTime(std::vector<Matrix4>& outPoses, const class Skeleton* inSkeleton, float inTime) const;

	void SetSkeleton(class Skeleton* skeleton) { mSkeleton = skeleton; }
private:
	bool LoadFromJSON(const std::string& fileName);
	bool LoadFromFBX(const std::string& fileName);

	// Number of bones for the animation
	size_t mNumBones;
	// Number of frames in the animation
	size_t mNumFrames;
	// Duration of the animation in seconds
	float mDuration;
	// Duration of each frame in the animation
	float mFrameDuration;
	// Transform information for each frame on the track
	// Each index in the outer vector is a bone, inner vector
	// is a frame
	std::vector<std::vector<BoneTransform>> mTracks;

	class Skeleton* mSkeleton;
};