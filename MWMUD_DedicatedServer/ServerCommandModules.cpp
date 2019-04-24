#include "ServerCommandModules.h"

// NETWORK COMMANDS
#include "PingCommand.h"

/* ABSTRACT BASE CLASS
 * Class from which all command modules are derived
 */

// STATIC
std::unordered_set<ServerCommandModule*> ServerCommandModule::activeModules;

void ServerCommandModule::registerModule(ServerCommandModule* module)
{
	activeModules.insert(module);
}

void ServerCommandModule::deregisterModule(ServerCommandModule* module)
{
	activeModules.erase(module);
}

const std::unordered_set<ServerCommandModule*> ServerCommandModule::getActiveModules()
{
	return activeModules;
}

ServerCommandModule::~ServerCommandModule()
{
	while (!commands.empty())
	{
		delete commands.back();
		commands.pop_back();
	}
}

// INSTANCED
std::vector<ServerCommand*> ServerCommandModule::getCommands() { return commands; }
std::string ServerCommandModule::getName() { return name; }

/* NETWORK COMMANDS
 * Commands related to client-server interaction
 */
NetworkCommands::NetworkCommands()
{
	name = "Network";

	commands.push_back(new PingCommand());

	ServerCommandModule::registerModule(this);
}

NetworkCommands::~NetworkCommands() { ServerCommandModule::deregisterModule(this); }
