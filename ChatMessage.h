#pragma once

#include <d2d1.h>
#include <vector>
#include <string>

enum class CHAT_MESSAGE_TYPE
{
	CMSG_GENERIC = 0,

	CMSG_SYSTEM_NOTIFICATION,	// system notifications such as login/logout, server status, etc.
};

struct ChatMessage
{
	CHAT_MESSAGE_TYPE cmt;
	std::wstring msg;
};
