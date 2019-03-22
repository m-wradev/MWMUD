#include "GlobalChat.h"

std::deque<std::wstring> GlobalChat::globalHistory;

const std::deque<std::wstring>* GlobalChat::getChat()
{
	return &globalHistory;
}