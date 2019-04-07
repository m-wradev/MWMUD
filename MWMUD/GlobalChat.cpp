#include "GlobalChat.h"

#include "Util.h"
#include "Dispatcher.h"
#include "GameEvent.h"

std::unordered_map<std::string, void(*)(std::string)> GlobalChat::chatCommands;

void GlobalChat::init()
{
	/*====================================================================
	 *	CLIENT-SIDE COMMANDS
	 *	Commands that don't require requesting updates from the server.
	 *====================================================================
	 */

	/*	CHAT COMMANDS
	 */
	chatCommands["clear"] = [](std::string params)
	{
		Dispatcher::notify(&ChatEvent(EVENT_TYPE::GEVT_CHAT_CLEARCHAT, L""));
	};

	/*====================================================================
	 *	SERVER-SIDE COMMANDS
	 *	Commands that need to be processed by the server.
	 *====================================================================
	 */
}

void GlobalChat::parse(std::wstring msgIn)
{
	std::string msg = Util::convert_wstring_to_string(msgIn);

	// User is sending a simple message
	if (msg[0] != '/')
	{
		Dispatcher::notify(&NetworkEvent(EVENT_TYPE::GEVT_NETWORK_CLIENT_DATASEND, msgIn));
	}
	// User is entering a command that we can handle here.
	else
	{
		auto commandEntry = chatCommands.find(msg.substr(1, msg.find_first_of(' ') - 1));
		if (commandEntry != chatCommands.end())
			(commandEntry->second)(msg);
	}
}