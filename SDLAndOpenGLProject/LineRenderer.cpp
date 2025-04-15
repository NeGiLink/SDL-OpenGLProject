#include "LineRenderer.h"
#include "Texture.h"
#include "Shader.h"
#include "Actor.h"
#include "WinMain.h"
#include "BaseScene.h"
#include "Renderer.h"

LineRenderer::LineRenderer(ActorObject* owner, class Shader* shader, int drawOrder)
	:Component(owner)
	,mShader(shader)
	, mDrawOrder(drawOrder)
	, mVisible(true)
{
	owner->GetGame()->GetWinMain()->GetRenderer()->AddLineSprite(this);
}

LineRenderer::~LineRenderer()
{
	GetOwner()->GetGame()->GetWinMain()->GetRenderer()->RemoveLineSprite(this);
}

void LineRenderer::Draw(Vector3 start, Vector3 end, Vector4 color)
{
	if (mShader) 
	{

	}
}
