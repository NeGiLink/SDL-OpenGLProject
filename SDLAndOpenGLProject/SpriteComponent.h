#pragma once
#include "Component.h"
#include "Texture.h"
#include "Shader.h"
#include "Actor.h"
#include "Renderer.h"
#include <SDL3/SDL.h>

//画像描画に使用するクラス
class SpriteComponent : public Component
{
public:
	// (下に引く順序は後ろに対応します)
	SpriteComponent(class ActorObject* owner, int drawOrder = 100);
	~SpriteComponent();

	virtual void Draw(class Shader* shader);
	virtual void SetTexture(class Texture* texture);

	int GetDrawOrder() const { return mDrawOrder; }
	int GetTexHeight() const { return mTexHeight; }
	int GetTexWidth() const { return mTexWidth; }

	void SetVisible(bool visible) { mVisible = visible; }
	bool GetVisible() const { return mVisible; }
protected:
	class Texture*	mTexture;
	int				mDrawOrder;
	float			mTexWidth;
	float			mTexHeight;
	bool			mVisible;
};