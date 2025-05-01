#pragma once
#include "UIScreen.h"
#include "Image.h"

//ダイアログボックスUIのクラス
//ほぼ手を加えていないので
//参考コードとほぼ同じ
class GameDialogBox : public UIScreen
{
public:
	// (下に引く順序は後ろに対応します)
	GameDialogBox(const string& text,
		std::function<void()> onOK);
	~GameDialogBox();
};