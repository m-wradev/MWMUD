#include "GlobalChat.h"

#include "Util.h"
#include "Dispatcher.h"
#include "GameEvent.h"

#include "MainMenuScreen.h"

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
	// Clear the chat output.
	chatCommands["clear"] = [](std::string params)
	{
		Dispatcher::notify(&ChatEvent(EVENT_TYPE::GEVT_CHAT_CLEARCHAT, L""));
	};

	/*====================================================================
	 *	SERVER-SIDE COMMANDS
	 *	Commands that either need to be processed by the server or require
	 *	data to be sent to or received from the server.
	 *====================================================================
	 */

	/*	NETWORK UTILITIES
	 */
	// Ping the server and display the latency.
	chatCommands["ping"] = [](std::string params)
	{
		Dispatcher::notify(&NetworkEvent(EVENT_TYPE::GEVT_NETWORK_CLIENT_DATASEND, params));
	};

	chatCommands["disconnect"] = [](std::string params)
	{
		Dispatcher::notify(&NetworkEvent(EVENT_TYPE::GEVT_NETWORK_CLIENT_DATASEND, params));
		//Dispatcher::notify(&ScreenEvent(EVENT_TYPE::GEVT_SCREEN_CLEARANDSET, new MainMenuScreen()));
	};
}

void GlobalChat::parse(std::wstring msgIn)
{
	std::string msg = Util::convert_wstring_to_string(msgIn);

	// User is sending a simple message
	if (msg[0] != '/')
	{
		Dispatcher::notify(&NetworkEvent(EVENT_TYPE::GEVT_NETWORK_CLIENT_DATASEND, msg));
	}
	// User is entering a command that we can handle here.
	else
	{
		// Strip away the forward slash
		auto commandEntry = chatCommands.find(msg.substr(1, msg.find_first_of(' ') - 1));
		if (commandEntry != chatCommands.end())
			(commandEntry->second)(msg);
	}
}