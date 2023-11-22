#include "StringUtils.h"

namespace nc
{
    std::string ToUpper(std::string stringInput)
    {
        for (char& character : stringInput)
        {
            if (character >= 'a' && character <= 'z') character -= 32;
        }
        return stringInput;
    }

    std::string ToLower(std::string stringInput)
    {
        for (char& character : stringInput)
        {
            if (character >= 'A' && character <= 'Z') character += 32;
        }
        return stringInput;
    }

    bool IsEqualIgnoreCase(std::string stringInput1, std::string stringInput2)
    {
        if (stringInput1.size() != stringInput2.size())
        {
            return false;
        }

        return std::equal(stringInput1.begin(), stringInput1.end(), stringInput2.begin(), stringInput2.end(), [](char a, char b)
            {
                return ::toupper(a) == ::toupper(b);
            });
    }

    std::string CreateUnique(const std::string& str)
    {
        static uint32_t unique = 0;
        return str + std::to_string(unique++);
    }
}

