#include "Util.h"

#include <locale>
#include <codecvt>

std::string Util::convert_wstring_to_string(std::wstring wstr_in)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
	return converter.to_bytes(wstr_in);
}

std::wstring Util::convert_string_to_wstring(std::string str_in)
{
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	return converter.from_bytes(str_in);
}

std::vector<std::string> Util::split_string(std::string str, char delim)
{
	std::stringstream ss(str);
	std::string item;
	std::vector<std::string> splitStrings;
	while (std::getline(ss, item, delim))
		splitStrings.push_back(item);

	return splitStrings;
}

bool Util::equalsIgnoreCase(std::string s1, std::string s2)
{
	if (s1.length() != s2.length())
		return false;

	for (int i = 0; i < s1.length(); i++)
		if (toupper(s1[i]) != toupper(s2[i]))
			return false;

	return true;
}
