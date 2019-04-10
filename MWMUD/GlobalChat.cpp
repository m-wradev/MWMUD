#include "GlobalChat.h"

#include "Util.h"
#include "Dispatcher.h"

std::vector<CommandModule*> GlobalChat::commandModules;

void GlobalChat::init()
{
	commandModules.push_back(new ChatCommands());
	commandModules.push_back(new NetworkCommands());
}

void GlobalChat::clean()
{
	// Release all command modules
	while (!commandModules.empty())
	{
		delete commandModules.back();
		commandModules.pop_back();
	}
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
		std::string& cmd_with_args = msg;

		// Help command is special and gets special treatment
		if (CommandModule::helpCommand.match(cmd_str))
		{
			CommandModule::helpCommand.execute(Util::split_string(cmd_with_args, ' '));
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
						cmd->execute(Util::split_string(cmd_with_args, ' '));
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