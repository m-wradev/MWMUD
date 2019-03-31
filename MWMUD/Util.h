#pragma once

#include <string>

namespace Util
{
	// Convert a wstring to a string
	std::string convert_wstring_to_string(std::wstring in);

	// Convert a string to a wstring
	std::wstring convert_string_to_wstring(std::string);
};
