#include "Util.h"

#include <sstream>

std::vector<std::string> Util::split_string(std::string str, char delim)
{
	std::stringstream ss(str);
	std::string item;
	std::vector<std::string> splitStrings;
	while (std::getline(ss, item, delim))
		splitStrings.push_back(item);

	return splitStrings;
}

bool Util::equals_ignore_case(std::string s1, std::string s2)
{
	if (s1.length() != s2.length())
		return false;

	for (int i = 0; i < s1.length(); i++)
		if (toupper(s1[i]) != toupper(s2[i]))
			return false;

	return true;
}