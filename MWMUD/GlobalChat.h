// TODO - Route all messages sent by the client and the server through here.
#pragma once

#include <string>
#include <unordered_map>

#include "Command.h"
#include "CommandModules.h"

class GlobalChat
{
private:
	static std::vector<CommandModule*> commandModules;

public:
	// Initialize the global chat system.
	static void init();
	// Clean up the global chat system (commands, command modules, etc).
	static void clean();

	// Parse a message sent by a user.
	// If the message is a command, parse the command and execute it.
	static void parse(std::wstring msgIn);
};
