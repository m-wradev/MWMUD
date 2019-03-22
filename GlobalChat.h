/* All in-game chat messages feed through this system.
 */
#pragma once

#include <string>
#include <deque>


class GlobalChat
{
private:
	static std::deque<std::wstring> globalHistory;	// history of all chat message types
	static int historyLimit;	// max number of messages to be stored

public:
	static const std::deque<std::wstring>* getChat();
};
