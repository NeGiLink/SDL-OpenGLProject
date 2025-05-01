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

