#pragma once
#include <string>
namespace nc
{
	std::string ToUpper(std::string stringInput);
	std::string ToLower(std::string stringInput);
	bool IsEqualIgnoreCase(std::string stringInput1, std::string stringInput2);
	std::string CreateUnique(const std::string& str);
}
