#pragma once
#include "SDL3.h"
#include "Assimp.h"
#include "Collision.h"

//マテリアル情報の構造体
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
	// MeshのVertexArrayを配列で取得
	std::vector<class VertexArray*> GetVertexArrays() { return mVertexArrays; }
	// テクスチャを配列で取得
	class Texture* GetTexture(size_t index);
	// シェーダー名を取得
	const std::string& GetShaderName() const { return mShaderName; }
	// 球の半径を取得
	std::vector<float> GetRadiusArray() const { return mRadiusArray; }
	// モデルのボックス型の座標を取得
	const std::vector<AABB> GetBoxs() const { return mBoxs; }
	//マテリアル情報取得
	const std::vector<MaterialInfo> GetMaterialInfo() const { return mMaterialInfo; }
	//Meshの数を取得
	int CheckMeshIndex(const std::string& fileName, class Renderer* renderer);
private:
	//JSONファイルの読み込み処理
	bool LoadFromJSON(const std::string& fileName, class Renderer* renderer, int index);
	// FBXファイルからJSONに変換処理
	bool LoadFromFBX(const std::string& fileName, class Renderer* renderer, int index);
	// AABBの当たり判定を配列で取得
	std::vector<AABB> mBoxs;
	// Meshのテクスチャを取得
	std::vector<class Texture*> mTextures;
	// MeshのVertexArrayの配列
	std::vector<class VertexArray*> mVertexArrays;
	// シェーダー名
	std::string mShaderName;
	// 球の半径
	std::vector<float> mRadiusArray;
	// マテリアル情報
	std::vector<MaterialInfo> mMaterialInfo;
};