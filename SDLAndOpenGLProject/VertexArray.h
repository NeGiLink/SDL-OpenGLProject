#pragma once

class VertexArray
{
public:
	// 頂点レイアウトタグ
	enum Layout
	{
		PosNormTex,
		PosNormSkinTex
	};

	VertexArray(const void* verts, unsigned int numVerts, Layout layout,
		const unsigned int* indices, unsigned int numIndices);
	~VertexArray();

	void SetActive();
	unsigned int GetNumIndices() const { return mNumIndices; }
	unsigned int GetNumVerts() const { return mNumVerts; }
private:
	//vertex bufferの頂点数
	unsigned int mNumVerts;
	// index bufferのインデックス数
	unsigned int mNumIndices;
	// 頂点バッファのOpenGL ID
	unsigned int mVertexBuffer;
	// インデックスバッファのOpenGL ID
	unsigned int mIndexBuffer;
	// 頂点配列オブジェクトのOpenGL ID
	unsigned int mVertexArray;
};