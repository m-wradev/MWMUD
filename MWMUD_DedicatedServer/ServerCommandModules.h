#pragma once
#include <unordered_set>

#include "ServerCommand.h"

class ServerCommandModule
{
protected:
	static std::unordered_set<ServerCommandModule*> activeModules;

	std::vector<ServerCommand*> commands;
	std::string name;

	// Add a module of commands to the set of active modules
	static void registerModule(ServerCommandModule*);
	// Remove a module of commands from the active modules
	static void deregisterModule(ServerCommandModule*);

public:
	static const std::unordered_set<ServerCommandModule*> getActiveModules();

	virtual ~ServerCommandModule();

	std::vector<ServerCommand*> getCommands();
	std::string getName();
};

// All commands related to network functionality/information
struct NetworkCommands : public ServerCommandModule
{
	NetworkCommands();
	~NetworkCommands();
};
