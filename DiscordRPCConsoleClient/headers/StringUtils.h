#pragma once 

#include <string>

namespace sutils {

    bool equalsIgnoreCase(const std::string& str1, const std::string& str2);

    void toLowerCase(std::string& str);

    void toUpperCase(std::string& str);
}