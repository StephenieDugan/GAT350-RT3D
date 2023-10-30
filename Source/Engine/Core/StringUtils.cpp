#include "StringUtils.h"
#include <cctype> // For std::tolower, std::toupper

namespace Twili
{
unsigned int StringUtils::value = 1; //initiallizes value

std::string StringUtils::ToUpper(const std::string& input) 
{
    std::string result = input;
    for (char& c : result) //for each loop for each character
    {
        c = std::toupper(c); //turns charcter uppercase
    }
    return result;
}

std::string StringUtils::ToLower(const std::string& input) 
{
    std::string result = input;
    for (char& c : result) //for each loop for each character
    {
        c = std::tolower(c);//turns charcter lowercase
    }
    return result;
}

bool StringUtils::IsEqualIgnoreCase(const std::string& str1, const std::string& str2) 
{
    return ToLower(str1) == ToLower(str2); //turns both lowercase and compares them
}

std::string StringUtils::CreateUnique(const std::string& input) 
{
    return input + std::to_string(value++);//adds 1 to value every time function is called so each name is unique
}

}

