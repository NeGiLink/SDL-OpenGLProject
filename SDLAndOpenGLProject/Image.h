#pragma once
#include "Math.h"
#include <cstdint>
#include <string>
#include <functional>
#include <vector>


class Image
{
public:
	Image(class BaseScene* game);
	virtual ~Image();
	virtual void Load(std::string file);
	virtual void SetPosition(Vector2 pos);
	virtual void Update(float deltaTime);
	virtual void Draw(class Shader* shader);
	// Tracks if the UI is active or closing
	enum UIState
	{
		EActive,
		EClosing
	};
	// Set state to closing
	void Close();
	// Get state of UI screen
	UIState GetState() const { return mState; }

protected:
	// Helper to draw a texture
	void DrawTexture(class Shader* shader, class Texture* texture,
		const Vector2& offset = Vector2::Zero,
		float scale = 1.0f);
	class BaseScene* mGame;

	class Texture* mTexture;

	// Configure positions
	Vector2 mTexturePos;
	Vector2 mNextButtonPos;
	Vector2 mBGPos;

	// State
	UIState mState;
};

