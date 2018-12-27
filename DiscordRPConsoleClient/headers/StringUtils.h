#pragma once 

#include <string>
#include <vector>

namespace sutils {

    bool equalsIgnoreCase(const std::string& str1, const std::string& str2);

    void trim(std::string& str);

    void toLowerCase(std::string& str);

    void toUpperCase(std::string& str);

    /**
     * Parse command line arguments and adds the to the vector.
     * This is a modified version of https://stackoverflow.com/a/30518617/9816236
     */
    void parseCommandLineArgs(const std::string& line, std::vector<std::string>& argsStorage);
}