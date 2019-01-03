#pragma once

#include <string>
#include <vector>

namespace sutils {

    bool equalsIgnoreCase(const std::string& str1, const std::string& str2);

    void trim(std::string& str);

    void addPaddingToRight(std::string& str, int minWidth);

    void toLowerCase(std::string& str);

    void toUpperCase(std::string& str);

    bool str2Int(int& result, char const* str, int base = 0);

    /**
     * Parse command line arguments and add them to the vector.
     * This is a modified version of https://stackoverflow.com/a/30518617/9816236
     */
    void parseCommandLineArgs(const std::string& line, std::vector<std::string>& argsStorage);
}