#ifndef STRINGUTILS_H
#define STRINGUTILS_H

#include <string>

namespace Twili 
{
    class StringUtils 
    {
    public:
        static std::string ToUpper(const std::string& input);
        static std::string ToLower(const std::string& input);
        static bool IsEqualIgnoreCase(const std::string& str1, const std::string& str2);
        static std::string CreateUnique(const std::string& input);

    private:
        static unsigned int value;
    };


}

#endif // STRINGUTILS_H