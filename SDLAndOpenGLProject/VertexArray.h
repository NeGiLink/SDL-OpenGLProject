#pragma once
#include <GL/glew.h>
#include "StandardLibrary.h"
#include "Math.h"

namespace VertexLayout
{
	//�e�^�̃o�C�g��
	constexpr size_t FLOAT_SIZE = sizeof(float);
	constexpr size_t UBYTE_SIZE = sizeof(unsigned char);

	constexpr GLsizei NUM_VERTEX_ARRAYS = 1;

	constexpr GLsizei NUM_VERTEX_BUFFERS = 1;

	constexpr GLsizei NUM_INDEX_BUFFERS = 1;

	//***glEnableVertexAttribArray�̃A�N�Z�X�C���f�b�N�X***
	//�ʒu�̒��_�����̃C���f�b�N�X
	constexpr size_t  POSITION_INDEX = 0;
	//�@���̒��_�����̃C���f�b�N�X
	constexpr size_t  NORMAL_INDEX = 1;
	//�e�N�X�`�����W(UV)�̒��_�����̃C���f�b�N�X
	constexpr size_t  MESH_TEXUV_INDEX = 2;
	//�E�F�C�g�̒��_�����̃C���f�b�N�X
	constexpr size_t  BONEWEIGHT_INDEX = 3;
	//�{�[���C���f�b�N�X�E�{�[���̃E�F�C�g�E�e�N�X�`�����̒��_�����̃C���f�b�N�X
	constexpr size_t  SKINMESH_TEXUV_INDEX = 4;


	// �����̍\���ifloat�T�C�Y�O��j
	constexpr size_t POSITION_COMPONENTS = 3;
	constexpr size_t NORMAL_COMPONENTS = 3;
	constexpr size_t TEXCOORD_COMPONENTS = 2;
	constexpr size_t WEIGHT_COMPONENTS = 4;
	constexpr size_t BONE_INDEX_COUNT = 4;

	//Position�I�t�Z�b�g�l
	constexpr size_t POSITION_OFFSET = 0;
	//Normal�I�t�Z�b�g�l
	constexpr size_t  NORMAL_OFFSET = POSITION_COMPONENTS;
	//Textrue���W�̃I�t�Z�b�g�l
	constexpr size_t  TEXTURE_OFFSET = POSITION_COMPONENTS + NORMAL_COMPONENTS;
	//�X�L�j���O�I�t�Z�b�g�l
	constexpr size_t  SKINNING_OFFSET = POSITION_COMPONENTS + NORMAL_COMPONENTS;
	//�X�L���E�F�C�g�I�t�Z�b�g�l
	constexpr size_t  SKINWEIGHT_OFFSET = POSITION_COMPONENTS + NORMAL_COMPONENTS;
	//�e�N�X�`���I�t�Z�b�g�l
	constexpr size_t  SKINTEXTURE_OFFSET = POSITION_COMPONENTS + NORMAL_COMPONENTS + WEIGHT_COMPONENTS;


	//Mesh�I�u�W�F�N�g�̒��_�T�C�Y
	constexpr size_t  MESHOBJECT_SIZE = POSITION_COMPONENTS + NORMAL_COMPONENTS + TEXCOORD_COMPONENTS;
	//SkinMesh�I�u�W�F�N�g�̒��_�T�C�Y
	constexpr size_t  SKINMESHOBJECT_SIZE = POSITION_COMPONENTS + NORMAL_COMPONENTS + TEXCOORD_COMPONENTS + BONE_INDEX_COUNT;

	//�e���_�̃T�C�Y(NormTex)
	constexpr size_t  NORMTEX_SIZE = MESHOBJECT_SIZE * FLOAT_SIZE;
	//�e���_�̃T�C�Y(NormSkinTex)
	constexpr size_t  NORMSKINTEX_SIZE = SKINMESHOBJECT_SIZE * FLOAT_SIZE + WEIGHT_COMPONENTS * UBYTE_SIZE;
}

//���Ќ������������t�@�C��
class VertexArray
{
private:
	//vertex buffer�̒��_��
	unsigned int	mNumVerts;
	// index buffer�̃C���f�b�N�X��
	unsigned int	mNumIndices;
	// ���_�o�b�t�@��OpenGL ID
	unsigned int	mVertexBuffer;
	// �C���f�b�N�X�o�b�t�@��OpenGL ID
	unsigned int	mIndexBuffer;
	// ���_�z��I�u�W�F�N�g��OpenGL ID
	unsigned int	mVertexArray;
public:
	// ���_���C�A�E�g�^�O
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