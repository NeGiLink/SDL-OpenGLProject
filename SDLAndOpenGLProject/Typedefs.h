#pragma once
#include "StandardLibrary.h"

//������̊ȈՋL�q����
typedef std::string string;

typedef char c_String;

typedef c_String* cp_String;

typedef const c_String* ccp_String;

typedef std::u8string u8string;

typedef std::stringstream stringstream;

typedef std::stringbuf stringbuf;
//vector�̊ȈՋL�q����
template <typename T>
using vector = std::vector<T>;
