#include "VertexArray.h"
#include <GL/glew.h>

VertexArray::VertexArray(const void* verts, unsigned int numVerts, Layout layout,
	const unsigned int* indices, unsigned int numIndices)
	:mNumVerts(numVerts)
	, mNumIndices(numIndices)
{
	// ���_�z����쐬����
	glGenVertexArrays(1, &mVertexArray);
	glBindVertexArray(mVertexArray);

	unsigned vertexSize = 8 * sizeof(float);
	if (layout == PosNormSkinTex)
	{
		//�E�F�C�g��GL_FLOAT�ɂ������߃T�C�Y�ύX
		vertexSize = 12 * sizeof(float) + 4 * sizeof(char);
	}

	// ���_�o�b�t�@���쐬����
	glGenBuffers(1, &mVertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, numVerts * vertexSize, verts, GL_STATIC_DRAW);

	// �C���f�b�N�X�o�b�t�@���쐬����
	glGenBuffers(1, &mIndexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(unsigned int), indices, GL_STATIC_DRAW);

	// ���_�������w�肵�Ă�������
	if (layout == PosNormTex)
	{
		// Position��3�̕��������_
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertexSize, 0);
		// Normal��3�̕��������_
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, vertexSize,
			reinterpret_cast<void*>(sizeof(float) * 3));
		// �e�N�X�`�����W��2�̕��������_��
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, vertexSize,
			reinterpret_cast<void*>(sizeof(float) * 6));
	}
	else if (layout == PosNormSkinTex)
	{
		// Position��3�̕��������_
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertexSize, 0);
		// Normal��3�̕��������_
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, vertexSize,
			reinterpret_cast<void*>(sizeof(float) * 3));
		// �X�L�j���O�C���f�b�N�X�i�����Ƃ��ĕێ��j
		glEnableVertexAttribArray(2);
		glVertexAttribIPointer(2, 4, GL_UNSIGNED_BYTE, vertexSize,
			reinterpret_cast<void*>(sizeof(float) * 6));
		// �X�L���E�F�C�g�i���������_�ɕϊ��j
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, vertexSize,
			reinterpret_cast<void*>(sizeof(float) * 6 + sizeof(char) * 4));
		// �e�N�X�`�����W
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, vertexSize,
			reinterpret_cast<void*>(sizeof(float) * 10 + sizeof(char) * 4));
	}
}


VertexArray::VertexArray(const float* verts, unsigned int numVerts)
	: mNumVerts(numVerts)
	, mNumIndices(0)
{
	glGenVertexArrays(1, &mVertexArray);
	glGenBuffers(1, &mVertexBuffer);

	glBindVertexArray(mVertexArray);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * numVerts, verts, GL_STATIC_DRAW);

	// �ʒu���������ivec3�j
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glBindVertexArray(0);
}

VertexArray::~VertexArray()
{
	glDeleteBuffers(1, &mVertexBuffer);
	glDeleteBuffers(1, &mIndexBuffer);
	glDeleteVertexArrays(1, &mVertexArray);
}

void VertexArray::SetActive()
{
	glBindVertexArray(mVertexArray);
}

