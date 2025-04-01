#pragma once
#include "Component.h"
#include <cstddef>
#include <vector>

class MeshComponent : public Component
{
public:
	MeshComponent(class ActorObject* owner, bool isSkeletal = false);
	~MeshComponent();
	// Draw this mesh component
	virtual void Draw(class Shader* shader);
	// Set the mesh/texture index used by mesh component
	virtual void SetMesh(class Mesh* mesh) 
	{
		mMeshs.push_back(mesh);
	}

	virtual void SetMeshs(const std::vector<class Mesh*>& mesh)
	{
		mMeshs.insert(mMeshs.end(), mesh.begin(), mesh.end());
	}

	void SetTextureIndex(size_t index) { mTextureIndex = index; }

	void SetVisible(bool visible) { mVisible = visible; }
	bool GetVisible() const { return mVisible; }

	bool GetIsSkeletal() const { return mIsSkeletal; }
protected:
	std::vector<class Mesh*> mMeshs;
	size_t mTextureIndex;
	bool mVisible;
	bool mIsSkeletal;
};

