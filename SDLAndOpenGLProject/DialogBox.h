#pragma once
#include "UIScreen.h"
//ダイアログボックスUIのクラス
//ほぼ手を加えていないので
//参考コードとほぼ同じ
class DialogBox : public UIScreen
{
public:
	// (下に引く順序は後ろに対応します)
	DialogBox(const std::string& text,
		std::function<void()> onOK);
	~DialogBox();
};

