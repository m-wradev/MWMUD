#pragma once

#include <string>
#include <sstream>
#include <vector>

namespace Util
{
	// Convert a wstring to a string
	std::string convert_wstring_to_string(std::wstring in);

	// Convert a string to a wstring
	std::wstring convert_string_to_wstring(std::string);

	// Split a string by a given delimiter
	std::vector<std::string> split_string(std::string str, char delim);

	// Compare two strings, ignoring the case
	bool equalsIgnoreCase(std::string s1, std::string s2);
};
