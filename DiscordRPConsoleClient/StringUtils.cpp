#include "pch.h"

#include "StringUtils.h"
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

    void trim(std::string& str) {
        size_t findex = str.find_first_not_of(' ');
        if (findex == std::string::npos) {
            return;
        }
        size_t lindex = str.find_last_not_of(' ');
        str = str.substr(findex, (lindex - findex + 1));
    }

    void toLowerCase(std::string& str) {
        std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    }

    void toUpperCase(std::string& str) {
        std::transform(str.begin(), str.end(), str.begin(), ::toupper);
    }

    void parseCommandLineArgs(const std::string& line, std::vector<std::string>& argsStorage) {
        const char SPACE = ' ', TAB = '\t';
        const char  DQUOTE = '\"', SQUOTE = '\'';

        // Copy the command line string to a character array.
        // strdup() uses malloc() to get memory for the new string.
    #if defined(WIN32)
        char* charArray = _strdup(line.c_str());
    #else
        char* charArray = strdup(line.c_str());
    #endif

        std::vector<char*> tokens;
        char* charArrayCursor = charArray;
        while (*charArrayCursor) {
            if (*charArrayCursor == SPACE || *charArrayCursor == TAB) {
                // Whitespace.
                ++charArrayCursor;
                continue;
            }
            char* pEnd;
            if (*charArrayCursor == '\"') {
                // Double quoted token.
                tokens.push_back(charArrayCursor + 1);
                *charArrayCursor = SPACE;
                pEnd = strchr(charArrayCursor + 1, DQUOTE);
            } else if (*charArrayCursor == SQUOTE) {
                // Single quoted token.
                tokens.push_back(charArrayCursor + 1);
                *charArrayCursor = SPACE;
                pEnd = strchr(charArrayCursor + 1, SQUOTE);
            } else {
                // Unquoted token.
                tokens.push_back(charArrayCursor);
                pEnd = strpbrk(charArrayCursor + 1, " \n\r\t"); // whitespace
            }
            // Check token.
            if (!pEnd) {
                // End of token is end of line.
                break;
            }
            // End of token is one char before the next whitespace/end quote.
            // Replace whitespace/the quote with terminator, and advance cursor.
            *pEnd = '\0'; // null terminator character
            charArrayCursor = pEnd + 1;
        }
        // Copy args to vector.
        for (std::vector<char*>::const_iterator it = tokens.begin(); it != tokens.end(); ++it) {
            argsStorage.emplace_back(*it);
        }
        // Remember to free the memory after copy because strdup() uses malloc() to get memory for the new string.
        free(charArray);
    }
}