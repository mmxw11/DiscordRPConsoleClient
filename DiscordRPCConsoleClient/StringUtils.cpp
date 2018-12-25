#include "pch.h"

#include "StringUtils.h"
#include <iostream>
#include <algorithm>

namespace sutils {

    bool equalsIgnoreCase(const std::string& str1, const std::string& str2) {
        if (str1.size() != str2.size()) {
            return false;
        }
        std::string str1Cpy(str1);
        std::string str2Cpy(str2);
        toUpperCase(str1Cpy);
        toUpperCase(str2Cpy);
        return str1Cpy == str2Cpy;
    }

    void toLowerCase(std::string& str) {
        std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    }
    void toUpperCase(std::string& str) {
        std::transform(str.begin(), str.end(), str.begin(), ::toupper);
    }
}