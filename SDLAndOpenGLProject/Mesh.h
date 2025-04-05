#pragma once
#include "SDL3.h"
#include "Assimp.h"
#include "Collision.h"

//�}�e���A�����̍\����
struct MaterialInfo
{
	Vector4 Color;
	Vector3 Diffuse;
	Vector3 Ambient;
	Vector3 Specular;
	float   Shininess;
};

class Mesh
{
public:
	Mesh();
	~Mesh();
	// Load
	bool Load(const std::string& fileName, class Renderer* renderer,int index);
	// Unload mesh
	void Unload();
	// Mesh��VertexArray��z��Ŏ擾
	std::vector<class VertexArray*> GetVertexArrays() { return mVertexArrays; }
	// �e�N�X�`����z��Ŏ擾
	class Texture* GetTexture(size_t index);
	// �V�F�[�_�[�����擾
	const std::string& GetShaderName() const { return mShaderName; }
	// ���̔��a���擾
	std::vector<float> GetRadiusArray() const { return mRadiusArray; }
	// ���f���̃{�b�N�X�^�̍��W���擾
	const std::vector<AABB> GetBoxs() const { return mBoxs; }
	//�}�e���A�����擾
	const std::vector<MaterialInfo> GetMaterialInfo() const { return mMaterialInfo; }
	//Mesh�̐����擾
	int CheckMeshIndex(const std::string& fileName, class Renderer* renderer);
private:
	//JSON�t�@�C���̓ǂݍ��ݏ���
	bool LoadFromJSON(const std::string& fileName, class Renderer* renderer, int index);
	// FBX�t�@�C������JSON�ɕϊ�����
	bool LoadFromFBX(const std::string& fileName, class Renderer* renderer, int index);
	// AABB�̓����蔻���z��Ŏ擾
	std::vector<AABB> mBoxs;
	// Mesh�̃e�N�X�`�����擾
	std::vector<class Texture*> mTextures;
	// Mesh��VertexArray�̔z��
	std::vector<class VertexArray*> mVertexArrays;
	// �V�F�[�_�[��
	std::string mShaderName;
	// ���̔��a
	std::vector<float> mRadiusArray;
	// �}�e���A�����
	std::vector<MaterialInfo> mMaterialInfo;
};