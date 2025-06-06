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
	//�g���q��������菜���֐�
	inline string RemoveExtension(const std::string& filename) {
		size_t dotPos = filename.rfind('.');
		if (dotPos != std::string::npos) {
			return filename.substr(0, dotPos);  // �g���q�̒��O�܂Ő؂�o��
		}
		return filename;  // �h�b�g���Ȃ���΂��̂܂ܕԂ�
	}
	//�w�肵���������r������֐�
	inline string RemoveString(const std::string& string, const std::string& removeString)
	{
		std::string s;
		//string����Path����������菜��
		// removeString���擪�ɂ��邩�`�F�b�N
		if (string.find(removeString) == 0) {
			// Model::ModelPath�̒�����������菜������������擾
			s = string.substr(removeString.length());
		}
		else {
			//SDL_Log("removeString not found at beginning");
			return "";
		}
		return s;
	}
};

