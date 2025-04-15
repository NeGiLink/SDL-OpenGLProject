#pragma once
#include "SDL3.h"
#include "Component.h"

//–¢Š®¬
class LineRenderer : public Component
{
public:
	// (‰º‚Éˆø‚­‡˜‚ÍŒã‚ë‚É‘Î‰‚µ‚Ü‚·)
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