#pragma once
#include <string>
class StringUtils
{
public:
	static std::string ToUpper(std::string stringInput);
	static std::string ToLower(std::string stringInput);
	static bool IsEqualIgnoreCase(std::string stringInput1, std::string stringInput2);
	static std::string CreateUnique(const std::string& str);
};

