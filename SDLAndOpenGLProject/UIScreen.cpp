#include "UIScreen.h"
#include "Texture.h"
#include "Shader.h"
#include "WinMain.h"
#include "BaseScene.h"
#include "Renderer.h"
#include "Font.h"

#include "Image.h"
#include "Text.h"

UIScreen::UIScreen(BaseScene* game)
	:mGame(game)
	, mTitle(nullptr)
	, mBackground(nullptr)
	, mTitlePos(0.0f, 300.0f)
	, mNextButtonPos(0.0f, 200.0f)
	, mBGPos(0.0f, 250.0f)
	, mState(EActive)
{
	// Add to UI Stack
	mGame->PushUI(this);
	mTitleFont = new Text(game, mGame->GetFont("Assets/Fonts/Carlito-Regular.ttf"),Vector2::Zero,false);
	
	mButtonOn = new Image(game, false);
	mButtonOn->Load("Assets/ButtonYellow.png");

	mButtonOff = new Image(game, false);
	mButtonOff->Load("Assets/ButtonBlue.png");
}

UIScreen::~UIScreen()
{
	/*
	if (mTitle)
	{
		mTitle->Unload();
		delete mTitle;
	}
	*/
	//mFontは独自更新のためここでアンロード
	if (mTitleFont) 
	{
		if (mTitleFont->GetTexture()) {
			mTitleFont->GetTexture()->Unload();
		}
		delete mTitleFont;
	}
	

	for (auto b : mButtons)
	{
		delete b;
	}
	mButtons.clear();
}

void UIScreen::Update(float deltaTime)
{

}

void UIScreen::Draw(Shader* shader)
{
	// Draw background (if exists)
	if (mBackground)
	{
		mBackground->SetPosition(mBGPos);
		mBackground->Draw(shader);
		//DrawTexture(shader, mBackground, mBGPos);
	}
	// Draw title (if exists)
	if (mTitleFont)
	{
		mTitleFont->SetPosition(mTitlePos);
		mTitleFont->Draw(shader);
	}
	// Draw buttons
	for (auto b : mButtons)
	{
		// Draw background of button
		Image* tex = b->GetHighlighted() ? mButtonOn : mButtonOff;
		tex->SetPosition(b->GetPosition());
		tex->Draw(shader);
		//DrawTexture(shader, tex, b->GetPosition());
		// Draw text of button
		//tex->SetTexture(b->GetNameTex());
		//tex->SetPosition(b->GetPosition());
		//tex->Draw(shader);
		DrawTexture(shader, b->GetNameTex(), b->GetPosition());
	}
	// Override in subclasses to draw any textures
}

void UIScreen::ProcessInput(const bool* keys)
{
	// Do we have buttons?
	if (!mButtons.empty())
	{
		// Get position of mouse
		float x, y;
		SDL_GetMouseState(&x, &y);
		// Convert to (0,0) center coordinates
		Vector2 mousePos(static_cast<float>(x), static_cast<float>(y));
		mousePos.x -= mGame->GetWinMain()->GetRenderer()->GetScreenWidth() * 0.5f;
		mousePos.y = mGame->GetWinMain()->GetRenderer()->GetScreenHeight() * 0.5f - mousePos.y;

		// Highlight any buttons
		for (auto b : mButtons)
		{
			if (b->ContainsPoint(mousePos))
			{
				b->SetHighlighted(true);
			}
			else
			{
				b->SetHighlighted(false);
			}
		}
	}
}

void UIScreen::HandleKeyPress(int key)
{
	switch (key)
	{
	case SDL_BUTTON_LEFT:
		if (!mButtons.empty())
		{
			for (auto b : mButtons)
			{
				if (b->GetHighlighted())
				{
					b->OnClick();
					break;
				}
			}
		}
		break;
	default:
		break;
	}
}

void UIScreen::Close()
{
	mState = EClosing;
}

void UIScreen::SetTitle(const std::string& text,
	const Vector3& color,
	int pointSize)
{
	// Clear out previous title texture if it exists
	/*
	if (mTitle)
	{
		mTitle->Unload();
		delete mTitle;
		mTitle = nullptr;
	}
	*/
	mTitleFont->SetColor(color);
	mTitleFont->SetFontSize(pointSize);
	mTitleFont->SetText(text);
	//mTitle = mFont->RenderText(text, color, pointSize);
}

void UIScreen::AddButton(const std::string& name, std::function<void()> onClick)
{
	Vector2 dims(static_cast<float>(mButtonOn->GetTexture()->GetWidth()),
		static_cast<float>(mButtonOn->GetTexture()->GetHeight()));
	Button* b = new Button(name, mTitleFont->GetFont(), onClick, mNextButtonPos, dims);
	mButtons.emplace_back(b);

	// Update position of next button
	// Move down by height of button plus padding
	mNextButtonPos.y -= mButtonOff->GetTexture()->GetHeight() + 20.0f;
}

void UIScreen::DrawTexture(class Shader* shader, class Texture* texture,
	const Vector2& offset, float scale)
{
	// Scale the quad by the width/height of texture
	Matrix4 scaleMat = Matrix4::CreateScale(
		static_cast<float>(texture->GetWidth()) * scale,
		static_cast<float>(texture->GetHeight()) * scale,
		1.0f);
	// Translate to position on screen
	Matrix4 transMat = Matrix4::CreateTranslation(
		Vector3(offset.x, offset.y, 0.0f));
	// Set world transform
	Matrix4 world = scaleMat * transMat;
	shader->SetMatrixUniform("uWorldTransform", world);
	// Set current texture
	texture->SetActive();
	// Draw quad
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}

void UIScreen::SetRelativeMouseMode(bool relative)
{
	if (relative)
	{
		SDL_SetWindowRelativeMouseMode(mGame->GetWinMain()->GetRenderer()->GetWindow(), true);
		// Make an initial call to get relative to clear out
		SDL_GetRelativeMouseState(nullptr, nullptr);
	}
	else
	{
		SDL_SetWindowRelativeMouseMode(mGame->GetWinMain()->GetRenderer()->GetWindow(),false);
	}
}

Button::Button(const std::string& name, Font* font,
	std::function<void()> onClick,
	const Vector2& pos, const Vector2& dims)
	:mOnClick(onClick)
	, mNameTex(nullptr)
	, mFont(font)
	, mPosition(pos)
	, mDimensions(dims)
	, mHighlighted(false)
{
	SetName(name);
}

Button::~Button()
{
	if (mNameTex)
	{
		mNameTex->Unload();
		delete mNameTex;
	}
}

void Button::SetName(const std::string& name)
{
	mName = name;

	if (mNameTex)
	{
		mNameTex->Unload();
		delete mNameTex;
		mNameTex = nullptr;
	}
	mNameTex = mFont->RenderText(mName);
}

bool Button::ContainsPoint(const Vector2& pt) const
{
	bool no = pt.x < (mPosition.x - mDimensions.x / 2.0f) ||
		pt.x >(mPosition.x + mDimensions.x / 2.0f) ||
		pt.y < (mPosition.y - mDimensions.y / 2.0f) ||
		pt.y >(mPosition.y + mDimensions.y / 2.0f);
	return !no;
}

void Button::OnClick()
{
	// Call attached handler, if it exists
	if (mOnClick)
	{
		mOnClick();
	}
}