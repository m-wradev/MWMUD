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