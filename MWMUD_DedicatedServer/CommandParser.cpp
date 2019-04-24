#include <iostream>

#include "CommandParser.h"
#include "Dispatcher.h"
#include "Util.h"

std::vector<ServerCommandModule*> CommandParser::commandModules;

void CommandParser::init()
{
	commandModules.push_back(new NetworkCommands());
}

void CommandParser::cleanup()
{
	// Release all command modules
	while (!commandModules.empty())
	{
		delete commandModules.back();
		commandModules.pop_back();
	}
}

void CommandParser::parse(std::string msg, Client* sender)
{
	if (msg[0] != ServerCommand::CMD_DELIM)
	{
		// Broadcast the message to all clients
		Dispatcher::enqueueEvent(new ServerEvent::BroadcastMessage(msg));
	}
	else
	{
		std::string cmd_str = msg.substr(1, msg.find_first_of(' ') - 1);
		std::string& cmd_with_args = msg;

		// Search to see if the command exists and is available
		for (ServerCommandModule* cmd_mod : commandModules)
		{
			for (ServerCommand* cmd : cmd_mod->getCommands())
			{
				if (cmd->match(cmd_str))
				{
					// Found command, so execute and return
					cmd->execute(Util::split_string(cmd_with_args, ' '), sender);
					return;
				}
			}
		}
	}
}
