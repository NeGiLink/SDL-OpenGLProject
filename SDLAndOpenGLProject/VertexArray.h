#pragma once
#include <GL/glew.h>
#include "StandardLibrary.h"
#include "Math.h"

class VertexArray
{
private:
	//vertex bufferの頂点数
	unsigned int	mNumVerts;
	// index bufferのインデックス数
	unsigned int	mNumIndices;
	// 頂点バッファのOpenGL ID
	unsigned int	mVertexBuffer;
	// インデックスバッファのOpenGL ID
	unsigned int	mIndexBuffer;
	// 頂点配列オブジェクトのOpenGL ID
	unsigned int	mVertexArray;
public:
	// 頂点レイアウトタグ
	enum Layout
	{
		PosNormTex,
		PosNormSkinTex
	};

					VertexArray(const void* verts, unsigned int numVerts, Layout layout,
								const unsigned int* indices, unsigned int numIndices);
					VertexArray(float fillAmount, int maxSegments);

					VertexArray(const float* verts, unsigned int numVerts);
					~VertexArray();

	void			SetActive();
	unsigned int	GetNumIndices() const { return mNumIndices; }
	unsigned int	GetNumVerts() const { return mNumVerts; }
};