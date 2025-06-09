#pragma once
#include "Math.h"

const size_t MAX_SKELETON_BONES = 96;

const size_t MAX_SKELETONBINBONE = 64;

struct MatrixPalette
{
	Matrix4 mEntry[MAX_SKELETON_BONES];
};
