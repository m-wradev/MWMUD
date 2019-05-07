#include "CommandModules.h" 

// CHAT COMMANDS
#include "ClearChatCommand.h"

// NETWORK COMMANDS
#include "PingCommand.h"
#include "DisconnectCommand.h"
#include "LoginCommand.h"
#include "LogoutCommand.h"

/* ABSTRACT BASE CLASS
 * Class from which all command modules are derived
 */
std::unordered_set<CommandModule*> CommandModule::activeModules;
HelpCommand CommandModule::helpCommand;

void CommandModule::registerModule(CommandModule* module) 
{ 
	for (Command* cmd : module->getCommands())
		helpCommand.registerCommand(cmd);

	activeModules.insert(module); 
}

void CommandModule::deregisterModule(CommandModule* module) 
{ 
	for (Command *cmd : module->getCommands())
		helpCommand.deregisterCommand(cmd);

	activeModules.erase(module); 
}

const std::unordered_set<CommandModule*> CommandModule::getActiveModules() { return activeModules; }

CommandModule::~CommandModule()
{
	while (!commands.empty())
	{
		delete commands.back();
		commands.pop_back();
	}
}

std::vector<Command*> CommandModule::getCommands() { return commands; }
std::string CommandModule::getName() { return name; }

/* GENERAL COMMANDS
 * General utility commands.
 */
GeneralCommands::GeneralCommands()
{
	name = "General";

	CommandModule::registerModule(this);
}

GeneralCommands::~GeneralCommands() { CommandModule::deregisterModule(this); }

/* CHAT COMMANDS
 * Commands related to the chat system and/or communication with other players. 
 */
ChatCommands::ChatCommands()
{
	name = "Chat";

	commands.push_back(new ClearChatCommand());

	CommandModule::registerModule(this);
}

ChatCommands::~ChatCommands() { CommandModule::deregisterModule(this); }

/* NETWORK COMMANDS
 * Commands related to the client-server interaction.
 */
NetworkCommands::NetworkCommands()
{
	name = "Network";

	commands.push_back(new PingCommand());
	commands.push_back(new DisconnectCommand());
	commands.push_back(new LoginCommand());
	commands.push_back(new LogoutCommand());

	CommandModule::registerModule(this);
}

NetworkCommands::~NetworkCommands() { CommandModule::deregisterModule(this); }