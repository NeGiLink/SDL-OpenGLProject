#pragma once
#include "Typedefs.h"
#include <iostream>
#include <cstdlib>

#define ERROREXITCODE 1

namespace ERROR
{
    /// <summary> 
    /// �G���[�������ɌĂяo�����R�[���o�b�N�֐� 
    /// </summary> 
    /// <param name="error_code"> 
    /// ���������G���[�R�[�h 
    /// </param> 
    /// <param name="description"> 
    /// �G���[���������� 
    /// </param> 
    inline void ErrorCallback(const char* description)
    {
        string log = description;
        std::cerr <<  "Error : " + log << std::endl;
        // �v���O�������ُ�I��������
        std::exit(1); 
    }
};

namespace WARNING
{
    inline void WarningCallback(const char* description)
    {
        string log = description;
        std::cerr << "Warning : " + log << std::endl;
    }
};