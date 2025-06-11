#include "VertexArray.h"

VertexArray::VertexArray(const void* verts, unsigned int numVerts, Layout layout,
	const unsigned int* indices, unsigned int numIndices)
	:mNumVerts(numVerts)
	, mNumIndices(numIndices)
{
	// ���_�z����쐬����
	glGenVertexArrays(VertexLayout::NUM_VERTEX_ARRAYS, &mVertexArray);
	glBindVertexArray(mVertexArray);

	unsigned vertexSize = VertexLayout::NORMTEX_SIZE;
	if (layout == PosNormSkinTex)
	{
		//�E�F�C�g��GL_FLOAT�ɂ������߃T�C�Y�ύX
		vertexSize = VertexLayout::NORMSKINTEX_SIZE;
	}

	// ���_�o�b�t�@���쐬����
	glGenBuffers(VertexLayout::NUM_VERTEX_BUFFERS, &mVertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, numVerts * vertexSize, verts, GL_STATIC_DRAW);

	// �C���f�b�N�X�o�b�t�@���쐬����
	glGenBuffers(VertexLayout::NUM_INDEX_BUFFERS, &mIndexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(unsigned int), indices, GL_STATIC_DRAW);

	// ���_�������w�肵�Ă�������
	if (layout == PosNormTex)
	{
		// Position��3�̕��������_
		glEnableVertexAttribArray(VertexLayout::POSITION_INDEX);
		glVertexAttribPointer(VertexLayout::POSITION_INDEX, VertexLayout::POSITION_COMPONENTS,
							  GL_FLOAT, GL_FALSE, vertexSize, VertexLayout::POSITION_OFFSET);

		// Normal��3�̕��������_
		glEnableVertexAttribArray(VertexLayout::NORMAL_INDEX);
		glVertexAttribPointer(VertexLayout::NORMAL_INDEX, VertexLayout::NORMAL_COMPONENTS,
			GL_FLOAT, GL_FALSE, vertexSize,
			reinterpret_cast<void*>(sizeof(float) * VertexLayout::NORMAL_OFFSET));

		// �e�N�X�`�����W��2�̕��������_��
		glEnableVertexAttribArray(VertexLayout::MESH_TEXUV_INDEX);
		glVertexAttribPointer(VertexLayout::MESH_TEXUV_INDEX, VertexLayout::TEXCOORD_COMPONENTS,
			GL_FLOAT, GL_FALSE, vertexSize,
			reinterpret_cast<void*>(sizeof(float) * VertexLayout::TEXTURE_OFFSET));
	}
	else if (layout == PosNormSkinTex)
	{
		// Position��3�̕��������_
		glEnableVertexAttribArray(VertexLayout::POSITION_INDEX);
		glVertexAttribPointer(VertexLayout::POSITION_INDEX, VertexLayout::POSITION_COMPONENTS,
			GL_FLOAT, GL_FALSE, vertexSize, VertexLayout::POSITION_OFFSET);
		
		// Normal��3�̕��������_
		glEnableVertexAttribArray(VertexLayout::NORMAL_INDEX);
		glVertexAttribPointer(VertexLayout::NORMAL_INDEX, VertexLayout::NORMAL_COMPONENTS,
			GL_FLOAT, GL_FALSE, vertexSize,
			reinterpret_cast<void*>(sizeof(float) * VertexLayout::NORMAL_OFFSET));
		
		// �X�L�j���O�C���f�b�N�X�i�����Ƃ��ĕێ��j
		glEnableVertexAttribArray(VertexLayout::MESH_TEXUV_INDEX);
		glVertexAttribIPointer(VertexLayout::MESH_TEXUV_INDEX, VertexLayout::BONE_INDEX_COUNT,
			GL_UNSIGNED_BYTE, vertexSize,
			reinterpret_cast<void*>(sizeof(float) * VertexLayout::SKINNING_OFFSET));
		
		// �X�L���E�F�C�g�i���������_�ɕϊ��j
		glEnableVertexAttribArray(VertexLayout::BONEWEIGHT_INDEX);
		glVertexAttribPointer(VertexLayout::BONEWEIGHT_INDEX, VertexLayout::WEIGHT_COMPONENTS,
			GL_FLOAT, GL_FALSE, vertexSize,
			reinterpret_cast<void*>(sizeof(float) * VertexLayout::SKINWEIGHT_OFFSET + sizeof(char) * VertexLayout::BONE_INDEX_COUNT));
		
		// �e�N�X�`�����W
		glEnableVertexAttribArray(VertexLayout::SKINMESH_TEXUV_INDEX);
		glVertexAttribPointer(VertexLayout::SKINMESH_TEXUV_INDEX, VertexLayout::TEXCOORD_COMPONENTS,
			GL_FLOAT, GL_FALSE, vertexSize,
			reinterpret_cast<void*>(sizeof(float) * VertexLayout::SKINTEXTURE_OFFSET + sizeof(char) * VertexLayout::BONE_INDEX_COUNT));
	}
}

VertexArray::VertexArray(float fillAmount, int maxSegments)
{
	struct Vertex
	{
		float position[VertexLayout::POSITION_COMPONENTS];
		float texCoord[VertexLayout::TEXCOORD_COMPONENTS];
	};

	int segments = std::max(1, static_cast<int>(maxSegments * fillAmount));
	float angleStep = fillAmount * 2.0f * Math::Pi / segments;

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	// ���S�_�i���_�AUV ���S�j
	vertices.push_back({
		{ 0.0f, 0.0f, 0.0f },
		{ 0.5f, 0.5f }
		});

	// �O���̐�`���_�𐶐�
	for (int i = 0; i <= segments; ++i)
	{
		float angle = i * angleStep;
		float x = cosf(angle) * 0.5f;
		float y = sinf(angle) * 0.5f;

		vertices.push_back({
			{ x, y, 0.0f },
			{ x + 0.5f, y + 0.5f } // UV���S(0.5, 0.5)
			});
	}

	// �C���f�b�N�X�iGL_TRIANGLES �̎O�p�`�t�@���j
	for (int i = 1; i <= segments; ++i)
	{
		indices.push_back(0);
		indices.push_back(i);
		indices.push_back(i + 1);
	}

	mNumVerts = static_cast<unsigned int>(indices.size());

	// OpenGL�o�b�t�@�����Ɛݒ�
	glGenVertexArrays(VertexLayout::NUM_VERTEX_ARRAYS, &mVertexArray);
	glGenBuffers(VertexLayout::NUM_VERTEX_BUFFERS, &mVertexBuffer);
	glGenBuffers(VertexLayout::NUM_INDEX_BUFFERS, &mIndexBuffer);

	glBindVertexArray(mVertexArray);

	glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

	// ���_�����i�ʒu�Flocation=0�AUV�Flocation=2�j
	glEnableVertexAttribArray(VertexLayout::POSITION_INDEX);
	glVertexAttribPointer(VertexLayout::POSITION_INDEX, VertexLayout::POSITION_COMPONENTS, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

	glEnableVertexAttribArray(VertexLayout::MESH_TEXUV_INDEX);
	glVertexAttribPointer(VertexLayout::MESH_TEXUV_INDEX, VertexLayout::TEXCOORD_COMPONENTS, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texCoord));
}

VertexArray::VertexArray(const float* verts, unsigned int numVerts)
	: mNumVerts(numVerts)
	, mNumIndices(0)
{
	glGenVertexArrays(VertexLayout::NUM_VERTEX_ARRAYS, &mVertexArray);
	glGenBuffers(VertexLayout::NUM_VERTEX_BUFFERS, &mVertexBuffer);

	glBindVertexArray(mVertexArray);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * numVerts, verts, GL_STATIC_DRAW);

	// �ʒu���������ivec3�j
	glEnableVertexAttribArray(VertexLayout::POSITION_INDEX);
	glVertexAttribPointer(VertexLayout::POSITION_INDEX, VertexLayout::POSITION_COMPONENTS, GL_FLOAT, GL_FALSE, VertexLayout::POSITION_COMPONENTS * sizeof(float), (void*)0);

	glBindVertexArray(0);
}

VertexArray::~VertexArray()
{
	glDeleteBuffers(VertexLayout::NUM_VERTEX_BUFFERS, &mVertexBuffer);
	glDeleteBuffers(VertexLayout::NUM_INDEX_BUFFERS, &mIndexBuffer);
	glDeleteVertexArrays(VertexLayout::NUM_VERTEX_ARRAYS, &mVertexArray);
}

void VertexArray::SetActive()
{
	glBindVertexArray(mVertexArray);
}

