#pragma once
#include <string>
#include <unordered_map>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3/SDL.h>
#include "Math.h"

//文字のフォントを読み込み、参照するクラス
class Font
{
public:
	Font(class BaseScene* game);
	~Font();

	// ファイルからのロード/アンロード
	bool Load(const std::string& fileName);
	void Unload();

	// 与えられた文字列とフォントを使用して、テクスチャに描画します。
	class Texture* RenderText(const std::string& textKey,
		const Vector3& color = Color::White,
		int pointSize = 30);
	// 与えられた文字列とフォントを使用して、テクスチャに描画する
	//上記との違いは自由に引数で取得した文字を取得できる所
	class Texture* RenderFreeText(const std::string& textKey,
		const Vector3& color = Color::White,
		int pointSize = 30);
private:
	// ポイントサイズとフォントデータのマップ
	std::unordered_map<int, TTF_Font*>	mFontData;
	class BaseScene*					mGame;
};