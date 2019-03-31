// TODO - Route all messages sent by the client and the server through here.
#pragma once

#include <string>
#include <unordered_map>

class GlobalChat
{
private:
	typedef void(*onCommand)(std::string);
	static std::unordered_map<std::string, onCommand> chatCommands;

public:
	// Initialize the global chat system.
	static void init();

	// Parse a message sent by a user.
	// If the message is a command, parse the command and execute it.
	static void parse(std::wstring msgIn);
};
