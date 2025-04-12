#pragma once
#include "Component.h"
#include <cstddef>
#include <vector>

class MeshRenderer : public Component
{
public:
	MeshRenderer(class ActorObject* owner, bool isSkeletal = false);
	~MeshRenderer();
	// ���̃��b�V���R���|�[�l���g��`��
	virtual void Draw(class Shader* shader);
	// ���b�V���R���|�[�l���g�Ŏg�p����郁�b�V��/�e�N�X�`���C���f�b�N�X��ݒ肷��
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

	std::vector<class Mesh*> GetMeshs() const { return mMeshs; }
protected:
	std::vector<class Mesh*>	mMeshs;
	size_t						mTextureIndex;
	bool						mVisible;
	bool						mIsSkeletal;
};