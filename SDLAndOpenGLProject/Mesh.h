#pragma once
#include <vector>
#include <string>
#include <array>
#include "Collision.h"

class Mesh
{
public:
	Mesh();
	~Mesh();
	// Load/unload mesh
	bool Load(const std::string& fileName, class Renderer* renderer,int index);
	void Unload();
	// Get the vertex array associated with this mesh
	std::vector<class VertexArray*> GetVertexArrays() { return mVertexArrays; }
	// Get a texture from specified index
	class Texture* GetTexture(size_t index);
	// Get name of shader
	const std::string& GetShaderName() const { return mShaderName; }
	// Get object space bounding sphere radius
	//float GetRadius() const { return mRadius; }
	std::vector<float> GetRadiusArray() const { return mRadiusArray; }
	// Get object space bounding box
	const std::vector<AABB> GetBoxs() const { return mBoxs; }
	// Get specular power of mesh
	//float GetSpecPower() const { return mSpecPower; }
	std::vector<float> GetSpecPowers() const { return mSpecPowers; }

	class Shader* GetMaterialShader() { return mMaterialShader; }

	void SetTextures(const std::string& fileName, class Renderer* renderer);

	int CheckMeshIndex(const std::string& fileName, class Renderer* renderer);
private:
	bool LoadFromJSON(const std::string& fileName, class Renderer* renderer, int index);
	// FBXƒtƒ@ƒCƒ‹‚©‚çJSON‚É•ÏŠ·Load
	bool LoadFromFBX(const std::string& fileName, class Renderer* renderer, int index);
	// AABB collision
	std::vector<AABB> mBoxs;
	// Textures associated with this mesh
	std::vector<class Texture*> mTextures;
	// Vertex array associated with this mesh
	std::vector<class VertexArray*> mVertexArrays;
	// Name of shader specified by mesh
	std::string mShaderName;
	// Stores object space bounding sphere radius
	//float mRadius;
	std::vector<float> mRadiusArray;
	// Specular power of surface
	//float mSpecPower;
	std::vector<float> mSpecPowers;
	//Material shader
	class Shader* mMaterialShader;
};