#pragma once
#include "Assimp.h"
#include "SOIL.h"
#include <GL/glew.h>
#include "SDL3.h"

//�摜�̓ǂݍ��݁A�Q�Ƃ��s�����Ƃ��J�v�Z���������N���X
class Texture
{
public:
					Texture();
					~Texture();

	bool			Load(const string& fileName);
	bool			LoadFromAssimp(const aiTexture* embeddedTex);
	void			Unload();
	void			CreateFromSurface(struct SDL_Surface* surface);
	void			CreateForRendering(int width, int height, unsigned int format);

	void			SetActive(int index = 0);
	void			SetNoActive(int index = 0);

	int				GetWidth() const { return mWidth; }
	int				GetHeight() const { return mHeight; }
	unsigned int	GetTextureID() const { return mTextureID; }
private:
	unsigned int	mTextureID;

	int				mWidth;
	
	int				mHeight;
};