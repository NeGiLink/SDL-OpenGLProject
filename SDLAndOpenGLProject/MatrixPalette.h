#pragma once
#include "Math.h"

/*
* ===エンジン内部処理/Engine internal processing===
*/

namespace SkeletonLayout
{
	const size_t MAX_SKELETON_BONES = 96;

	const size_t MAX_SKELETONBINBONE = 64;
}


struct MatrixPalette
{
	Matrix4 mEntry[SkeletonLayout::MAX_SKELETON_BONES];
};
