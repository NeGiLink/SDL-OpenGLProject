#pragma once
#include "Typedefs.h"
#include <iostream>
#include <cstdlib>

#define ERROREXITCODE 1

namespace ERROR
{
    /// <summary> 
    /// エラー発生時に呼び出されるコールバック関数 
    /// </summary> 
    /// <param name="error_code"> 
    /// 発生したエラーコード 
    /// </param> 
    /// <param name="description"> 
    /// エラー説明文字列 
    /// </param> 
    inline void ErrorCallback(const char* description)
    {
        string log = description;
        std::cerr <<  "Error : " + log << std::endl;
        // プログラムを異常終了させる
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