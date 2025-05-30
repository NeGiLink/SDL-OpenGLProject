#pragma once
#include "SDL3.h"
#include "Component.h"

//未完成
class LineRenderer : public Component
{
public:
	// (下に引く順序は後ろに対応します)
	LineRenderer(class ActorObject* owner,class Shader* shader, int drawOrder = 100);
	~LineRenderer();

	virtual void Draw(Vector3 start,Vector3 end,Vector4 color);

	int GetDrawOrder() const { return mDrawOrder; }

	void SetVisible(bool visible) { mVisible = visible; }
	bool GetVisible() const { return mVisible; }
protected:
	int				mDrawOrder;
	bool			mVisible;

	class Shader* mShader;
};