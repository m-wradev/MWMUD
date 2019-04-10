// TODO - Route all messages sent by the client and the server through here.
#pragma once

#include <string>
#include <unordered_map>

#include "Command.h"
#include "CommandModules.h"

class GlobalChat
{
private:
	typedef void(*onCommand)(std::string);
	static std::vector<Command*> chatCommandsTest;
	static std::vector<CommandModule*> commandModules;

public:
	// Initialize the global chat system.
	static void init();

	// Parse a message sent by a user.
	// If the message is a command, parse the command and execute it.
	static void parse(std::wstring msgIn);
};
