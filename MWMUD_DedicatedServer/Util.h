#pragma once

#include <string>
#include <vector>

namespace Util
{
	// Split a string by a given delimiter
	std::vector<std::string> split_string(std::string str, char delim);

	// Compare two strings, ignoring the case
	bool equals_ignore_case(std::string s1, std::string s2);
};
