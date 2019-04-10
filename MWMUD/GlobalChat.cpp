#include "GlobalChat.h"

#include "Util.h"
#include "Dispatcher.h"
#include "GameEvent.h"

#include "HelpCommand.h"
#include "ClearChatCommand.h"

#include "MainMenuScreen.h"

std::vector<Command*> GlobalChat::chatCommandsTest;
std::vector<CommandModule*> GlobalChat::commandModules;

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
	/*
	chatCommands["clear"] = [](std::string params)
	{
		Dispatcher::enqueueEvent(new ChatEvent(EVENT_TYPE::GEVT_CHAT_CLEARCHAT, L""));
	};
	*/

	/*====================================================================
	 *	SERVER-SIDE COMMANDS
	 *	Commands that either need to be processed by the server or require
	 *	data to be sent to or received from the server.
	 *====================================================================
	 */

	/*	NETWORK UTILITIES
	 */
	// Ping the server and display the latency.
	/*
	chatCommands["ping"] = [](std::string params)
	{
		Dispatcher::enqueueEvent(new NetworkEvent(EVENT_TYPE::GEVT_NETWORK_CLIENT_DATASEND, params));
	};

	chatCommands["disconnect"] = [](std::string params)
	{
		Dispatcher::enqueueEvent(new NetworkEvent(EVENT_TYPE::GEVT_NETWORK_CLIENT_DATASEND, params));
		Dispatcher::enqueueEvent(new ScreenEvent(EVENT_TYPE::GEVT_SCREEN_CLEARANDSET, new MainMenuScreen()));
	};
	*/

	commandModules.push_back(new ChatCommands());
}

void GlobalChat::parse(std::wstring msgIn)
{
	std::string msg = Util::convert_wstring_to_string(msgIn);

	// User is sending a simple message
	if (msg[0] != Command::CMD_DELIM)
	{
		Dispatcher::enqueueEvent(new NetworkEvent(EVENT_TYPE::GEVT_NETWORK_CLIENT_DATASEND, msg));
	}
	// User is entering a command that we can handle here.
	else
	{
		Dispatcher::enqueueEvent(new ChatEvent(EVENT_TYPE::GEVT_CHAT_MESSAGEDISPLAY, msgIn));

		// Strip away the forward slash
		std::string cmd_str = msg.substr(1, msg.find_first_of(' ') - 1);
		int args_begin = msg.find_first_of(' ') + 1;
		std::string args_str = (args_begin > 0) ? msg.substr(args_begin) : "";

		// Help command is special and gets special treatment
		if (CommandModule::helpCommand.match(cmd_str))
		{
			CommandModule::helpCommand.execute(Util::split_string(args_str, ' '));
		}
		else
		{
			// If not the help command, search until we find the correct command
			for (CommandModule* cmd_mod : commandModules)
			{
				for (Command* cmd : cmd_mod->getCommands())
				{
					if (cmd->match(cmd_str))
					{
						// Found the command, so execute and return
						cmd->execute(Util::split_string(args_str, ' '));
						return;
					}
				}
			}

			// We never found a command matching the user's input string
			std::wstring errmsg = L"The command " + Util::convert_string_to_wstring(cmd_str) +
				L" either does not exist or isn't registered with a command module. Did you" +
				L" enter it correctly?";
			Dispatcher::enqueueEvent(new ChatEvent(EVENT_TYPE::GEVT_CHAT_MESSAGEDISPLAY, errmsg));
		}
	}
}