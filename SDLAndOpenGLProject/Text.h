#pragma once
#include "Math.h"
#include "Image.h"
#include <cstdint>
#include <string>
#include <functional>
#include <vector>

class Text : public Image
{
public:
	Text(class BaseScene* game, class Font* font,
		const Vector2& pos);
	~Text();

	// Set the name of the button
	void SetText(const std::string& name);

	void SetFontSize(int size);

	void SetColor(Vector3 color);
private:
	std::string mName;
	class Font* mFont;
	Vector2 mDimensions;
	bool mHighlighted;

	int mFontSize;

	Vector3 mColor;
};