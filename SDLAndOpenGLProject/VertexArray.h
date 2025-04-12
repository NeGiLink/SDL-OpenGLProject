#pragma once

class VertexArray
{
public:
	// ���_���C�A�E�g�^�O
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
	//vertex buffer�̒��_��
	unsigned int mNumVerts;
	// index buffer�̃C���f�b�N�X��
	unsigned int mNumIndices;
	// ���_�o�b�t�@��OpenGL ID
	unsigned int mVertexBuffer;
	// �C���f�b�N�X�o�b�t�@��OpenGL ID
	unsigned int mIndexBuffer;
	// ���_�z��I�u�W�F�N�g��OpenGL ID
	unsigned int mVertexArray;
};