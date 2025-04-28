#pragma once
#include "Component.h"
#include "Shader.h"
#include "Mesh.h"
#include "Actor.h"
#include "Texture.h"
#include "VertexArray.h"

//メッシュの描画を行うクラス
//読み込んだメッシュをセットして使用する
class MeshRenderer : public Component
{
public:
	MeshRenderer(class ActorObject* owner, bool isSkeletal = false);
	~MeshRenderer();
	// このメッシュコンポーネントを描画
	virtual void Draw(class Shader* shader);
	// メッシュコンポーネントで使用されるメッシュ/テクスチャインデックスを設定する
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