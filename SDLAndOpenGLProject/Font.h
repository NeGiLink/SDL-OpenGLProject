#pragma once
#include <string>
#include <unordered_map>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3/SDL.h>
#include "Math.h"

//�����̃t�H���g��ǂݍ��݁A�Q�Ƃ���N���X
class Font
{
public:
	Font(class BaseScene* game);
	~Font();

	// �t�@�C������̃��[�h/�A�����[�h
	bool Load(const std::string& fileName);
	void Unload();

	// �^����ꂽ������ƃt�H���g���g�p���āA�e�N�X�`���ɕ`�悵�܂��B
	class Texture* RenderText(const std::string& textKey,
		const Vector3& color = Color::White,
		int pointSize = 30);
	// �^����ꂽ������ƃt�H���g���g�p���āA�e�N�X�`���ɕ`�悷��
	//��L�Ƃ̈Ⴂ�͎��R�Ɉ����Ŏ擾�����������擾�ł��鏊
	class Texture* RenderFreeText(const std::string& textKey,
		const Vector3& color = Color::White,
		int pointSize = 30);
private:
	// �|�C���g�T�C�Y�ƃt�H���g�f�[�^�̃}�b�v
	std::unordered_map<int, TTF_Font*>	mFontData;
	class BaseScene*					mGame;
};