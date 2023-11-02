#include "StringUtils.h"
#include <cctype>
#include <sstream>

std::string ToUpper(const std::string& str) {
    std::string result = str;
    for (char& c : result) {
        c = std::toupper(c);
    }
    return result;
}

std::string ToLower(const std::string& str) {
    std::string result = str;
    for (char& c : result) {
        c = std::tolower(c);
    }
    return result;
}

bool IsEqualIgnoreCase(const std::string& str1, const std::string& str2) {
    if (str1.size() != str2.size()) {
        return false;
    }
    for (size_t i = 0; i < str1.size(); ++i) {
        if (std::tolower(str1[i]) != std::tolower(str2[i])) {
            return false;
        }
    }
    return true;
}

std::string CreateUnique(const std::string& str) {
    static unsigned int counter = 0;
    std::ostringstream oss;
    oss << str << counter++;
    return oss.str();
}
