#pragma once
#include "Canvas.h"
#include "Image.h"

//ダイアログボックスUIのクラス
//ほぼ手を加えていないので
////書籍元のファイル
class GameDialogBox : public Canvas
{
private:
	Button* mButton01;

	Button* mButton02;
public:
	// (下に引く順序は後ろに対応します)
	GameDialogBox(const string& text,
		std::function<void()> onOK);
	GameDialogBox(const char8_t* text,
		std::function<void()> onOK);
	~GameDialogBox();
};