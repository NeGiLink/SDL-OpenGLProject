#pragma once
#include "Typedefs.h"
#include <iostream>
#include <sstream>
#include <iomanip>

namespace FloatToString 
{
	inline string ToStringWithoutDecimal(float value) {
        std::ostringstream oss;
        oss << std::fixed << std::setprecision(0) << value;
        return oss.str();
    }
};

namespace StringConverter
{
	inline string removeExtension(const std::string& filename) {
		size_t dotPos = filename.rfind('.');
		if (dotPos != std::string::npos) {
			return filename.substr(0, dotPos);  // 拡張子の直前まで切り出す
		}
		return filename;  // ドットがなければそのまま返す
	}

	inline string RemoveString(const std::string& string, const std::string& removeString)
	{
		std::string s;
		//stringからPath部分だけ取り除く
		// removeStringが先頭にあるかチェック
		if (string.find(removeString) == 0) {
			// Model::ModelPathの長さ分だけ取り除いた文字列を取得
			s = string.substr(removeString.length());
		}
		else {
			//SDL_Log("removeString not found at beginning");
			return "";
		}
		return s;
	}
};

