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
		if (sender->isLoggedIn())
		{
			msg = sender->getName() + ": " + msg;
			Dispatcher::enqueueEvent(new ServerEvent::Message::Broadcast(msg));
		}
		else
		{
			sender->sendMessage("SERVER: You may only send messages while logged in to a character.  Use the /login command to log in.");
		}
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
