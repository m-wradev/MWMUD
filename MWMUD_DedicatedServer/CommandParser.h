#pragma once
#include <vector>

#include "Client.h"
#include "ServerCommandModules.h"

class SeverNetwork;

class CommandParser
{
private:
	static std::vector<ServerCommandModule*> commandModules;

public:
	// Init parser
	static void init();
	// Clean up
	static void cleanup();

	// Parse a message sent by a user/client.
	// If the message is a command, parse and execute it.
	static void parse(std::string, Client*);
};

