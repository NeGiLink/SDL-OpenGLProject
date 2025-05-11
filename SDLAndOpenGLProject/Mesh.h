#pragma once
#include "SDL3.h"
#include "Assimp.h"
#include "Collision.h"
#include "Renderer.h"
#include "Texture.h"
#include "VertexArray.h"
#include "FilePath.h"


//�}�e���A�����̍\����
struct MaterialInfo
{
	Vector4 Color;
	Vector3 Diffuse;
	Vector3 Ambient;
	Vector3 Specular;
	float   Shininess;
};

struct MeshBinHeader {
	uint32_t	layoutType;
	uint32_t	vertexCount;
	uint32_t	indexCount;
	Vector3		min;
	Vector3		max;
	float		colliderRadius;
};

class Mesh
{
public:
	Mesh();
	~Mesh();
	// Load
	bool Load(const string& fileName, class Renderer* renderer,int index);
	// �o�C�i���t�@�C������̓ǂݍ��ݏ���
	bool LoadFromMeshBin(const string& fileName, Renderer* renderer, int index);
	//Mesh�̐����擾
	int CheckMeshIndex(const string& fileName, class Renderer* renderer);
	// Unload mesh
	void Unload();
	// Getter
	// Mesh��VertexArray��z��Ŏ擾
	vector<class VertexArray*> GetVertexArrays() {return mVertexArrays; }
	// �e�N�X�`����z��Ŏ擾
	class Texture* GetTexture(size_t index);
	// �V�F�[�_�[�����擾
	const string& GetShaderName() const { return mShaderName; }
	// ���̔��a���擾
	vector<float> GetRadiusArray() const { return mRadiusArray; }
	// ���f���̃{�b�N�X�^�̍��W���擾
	const vector<AABB> GetBoxs() const { return mBoxs; }
	//�}�e���A�����擾
	const vector<MaterialInfo> GetMaterialInfo() const { return mMaterialInfo; }
private:
	//JSON�t�@�C���̓ǂݍ��ݏ���
	bool LoadFromJSON(const string& fileName, class Renderer* renderer, int index);
	// FBX�t�@�C������JSON�ɕϊ�����
	bool LoadFromFBX(const string& fileName, class Renderer* renderer, int index);
	// AABB�̓����蔻���z��Ŏ擾
	vector<AABB>				mBoxs;
	// Mesh�̃e�N�X�`�����擾
	vector<class Texture*>		mTextures;
	// Mesh��VertexArray�̔z��
	vector<class VertexArray*>  mVertexArrays;
	// �V�F�[�_�[��
	string						mShaderName;
	// ���̔��a
	vector<float>				mRadiusArray;
	// �}�e���A�����
	vector<MaterialInfo>		mMaterialInfo;
};