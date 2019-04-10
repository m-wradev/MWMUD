#pragma once

#include <unordered_set>

#include "Command.h"
#include "HelpCommand.h"

class CommandModule
{
protected:
	static std::unordered_set<CommandModule*> activeModules;

	std::vector<Command*> commands;
	std::string name;

	// Add a module of commands to the set of active modules
	static void registerModule(CommandModule*);
	// Remove a module of commands from the active modules
	static void deregisterModule(CommandModule*);

public:
	// The help command is special since all commands are registered to it
	static HelpCommand helpCommand;
	static const std::unordered_set<CommandModule*> getActiveModules();

	virtual ~CommandModule();
	
	std::vector<Command*> getCommands();
	std::string getName();
};

struct GeneralCommands : public CommandModule
{
	GeneralCommands();
	~GeneralCommands();
};

struct ChatCommands : public CommandModule
{
	ChatCommands();
	~ChatCommands();
};

struct NetworkCommands : public CommandModule
{
	NetworkCommands();
	~NetworkCommands();
};
