#pragma once
#include "Typedefs.h"
#include "Math.h"
#include <iostream>
#include <cstdlib>

/*
* ===�G���W����������/Engine internal processing===
*/

//�G���[�A�x���A�f�o�b�O�p�̃��O���o�͂���֐����܂Ƃ߂Ă���
//�G���W�����������̂��߁A�w�b�_�[�t�@�C���𕪂��Ă��܂���
namespace Debug
{
    /// <summary> 
    /// �G���[�������̃��O���o�͂������I��������֐� 
    /// </summary> 
    /// <param name="description"> 
    /// �G���[���������� 
    /// </param> 
    // �ėp�I��Error���O�i����������o�[�W�����j
    template <typename... Args>
    inline void ErrorLog(const char* format, Args... args)
    {
        std::string finalFormat = std::string("Error : ") + format;
        fprintf(stderr, finalFormat.c_str(), args...);
    }

    // �������Ȃ��o�[�W����
    inline void ErrorLog(const char* message)
    {
        std::string finalMessage = std::string("Error : ") + message;
        fprintf(stderr, "%s", finalMessage.c_str());
    }

    /// <summary> 
    /// �x���������̃��O���o�͂���֐� 
    /// </summary> 
    /// <param name="description"> 
    /// �x������������ 
    /// </param> 
    // �ėp�I��Warning���O�i����������o�[�W�����j
    template <typename... Args>
    inline void WarningLog(const char* format, Args... args)
    {
        std::string finalFormat = std::string("Warning : ") + format;
        fprintf(stderr, finalFormat.c_str(), args...);
    }

    // �������Ȃ��o�[�W����
    inline void WarningLog(const char* message)
    {
        std::string finalMessage = std::string("Warning : ") + message;
        fprintf(stderr, "%s", finalMessage.c_str());
    }


    inline void Log(const char* format)
    {
        fprintf(stderr, "%s", format);
        fprintf(stderr, "\n");
    }

    template <typename... Args>
    inline void Log(const char* format, Args... args)
    {
        fprintf(stderr, format, args...);
        fprintf(stderr, "\n");
    }
};